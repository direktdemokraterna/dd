<?php
  $list_of_votes_from_db = db_vote::get_prio_vote_ballots($_GET['id']);
  $list_of_votes = Array();
  foreach($list_of_votes_from_db as $row){
    $list_of_votes[] = Array("user_code" => $row['user_code'], "prio_ranking" => $row['prio_ranking'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
  }
  $prio_vote_result = vote_helpers::calculate_prio_vote_result($_GET['id']);
?>

<script>
  var user_id = <?php echo json_encode($_SESSION['id']); ?>;
  var vote_id = <?php echo json_encode($voteinfo['vote_id']); ?>;
  var constituency_id = <?php echo json_encode($voteinfo['constituency_id']); ?>;
  var list_of_votes = <?php echo json_encode($list_of_votes); ?>;
  <?php
    if($_SESSION['acting_as_delegate']){
      $delegate_id = db_delegate::get_delegate_id_from_user_id($_SESSION['id']);
      $check_delegate_constituency_access = db_constituency::check_delegate_constituency_access($delegate_id, $voteinfo['constituency_id']);
    }
  ?>
  var acting_as_delegate = <?php if(!empty($check_delegate_constituency_access)) echo "true"; else echo "false"; ?>;
  var number_of_alternatives = <?php echo json_encode($voteinfo['number_of_alternatives']); ?>;
</script>


<h1><?php if($voteinfo['type'] == "prio-vote") echo "Prioritetsomröstning:"; else echo "Personval:"; ?> <?php echo $voteinfo['title']; ?></h1>

<div class="vote_result_box">
  Ställningen i denna omröstning är: <br>

  <p>
  <?php
    if($voteinfo['type'] == "prio-vote"){
      if(empty($prio_vote_result)){
        echo "Inga alternativ att visa.";
      }
      else{
        vote_helpers::output_prio_vote_result($prio_vote_result);
      }
    }
    else{
      if(empty($prio_vote_result)){
        echo "Inga kandidater att visa.";
      }
      else{
        vote_helpers::output_candidate_election_result($prio_vote_result);
      }
    }
  ?>
  </p>

  <p>
  <?php if($voteinfo['status'] == "ended" || $voteinfo['status'] == "finished") : ?>
    Omröstningen är avslutad. Den avslutades <?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?>.
  <?php elseif($voteinfo['status'] == "del_ended") : ?>
    Omröstningen avslutas <?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?>. För delegater stängdes röstningsmöjligheten <?php echo general_helpers::show_date($voteinfo['timestamp_delegate_ended']); ?>.
  <?php elseif($voteinfo['status'] == "continuous") : ?>
    Det här är en kontinuerlig omröstning och fortsätter tills en votering bestämmer att den ska avslutas.
  <?php else : ?>
    Omröstningen avslutas <?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?>. För delegater stänger röstningsmöjligheten <?php echo general_helpers::show_date($voteinfo['timestamp_delegate_ended']); ?>.
  <?php endif; ?>
  </p>
</div>


<p>
<strong>Valkrets: </strong><?php echo $voteinfo['constituency_name']; ?><br>
<?php if($voteinfo['proposition_created']) : ?>
  <strong>Propositionen skapad: </strong><?php echo general_helpers::show_date($voteinfo['proposition_created']); ?><br>
  <strong>Propositionen skapad av: </strong><a href="index.php?type=member&action=view&id=<?php echo $voteinfo['user_id']; ?>"><?php echo $voteinfo['user_full_name']; ?></a><br>
<?php else : ?>
  <strong>Omröstningen skapad av administratör</strong><br>
<?php endif; ?>
<strong>Omröstningen startad: </strong><?php echo general_helpers::show_date($voteinfo['timestamp_created']); ?><br>
<?php if($voteinfo['status'] == "continuous") : ?>
  <strong>Omröstningen är kontinuerlig.</strong><br>
<?php else : ?>
  <strong>Delegatröstning avslutas: </strong><?php echo general_helpers::show_date($voteinfo['timestamp_delegate_ended']); ?><br>
  <strong>Personlig röstning avslutas: </strong><?php echo general_helpers::show_date($voteinfo['timestamp_ended']); ?><br>
<?php endif; ?>
<strong>Antal lagda röster: </strong><?php echo $voteinfo['number_of_ballots']; ?><br>
<strong>Varav personligt lagda röster: </strong><?php echo $voteinfo['number_of_direct_ballots']; ?><br>


<strong>Beskrivning:</strong><br>
<?php echo nl2br($voteinfo['description']); ?>
</p>

<?php if($user_allowed_to_vote) : ?>

  <p><a href="index.php?type=forum&action=show_posts&id=<?php echo $voteinfo['forum_topic_id']; ?>">Länk till denna omröstnings forumdebatt</a></p>

  <div class="vote_box">

  <?php if($voteinfo['status'] == "active" || ($voteinfo['status'] == "del_ended" && !$_SESSION['acting_as_delegate'])) : ?>

    Rangordna alternativen:<br>
  
    <form method="post" action="" class="prio-vote">
      <input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">
      <input type="hidden" name="ballot" id="ballot" value="">

      <ul class="prio-vote-box support-box" id="support-list"></ul>

      <ul class="prio-vote-box unsorted-box">

        <?php
          if($voteinfo['type'] == "prio-vote"){
            $votes_alternatives = db_vote::get_alternatives_for_vote($voteinfo['vote_id']);
          }
          else{
            $votes_alternatives = db_vote::get_candidates_for_vote($voteinfo['vote_id']);
          }
        ?>

        <?php foreach($votes_alternatives as $row) : ?>
          <?php if($voteinfo['type'] == "prio-vote") : ?>
            <li class="sortable" id="<?php echo $row['id']; ?>"><span title="<?php echo $row['description']; ?>"><?php echo $row['title']; ?></span></li>
          <?php else : ?>
            <li class="sortable" id="<?php echo $row['id']; ?>"><span title="<?php echo $row['description']; ?>"><?php echo $row['user_name']; ?></span></li>
          <?php endif; ?>
        <?php endforeach; ?>

      </ul>

      <ul class="prio-vote-box reject-box" id="reject-list"></ul>

      <input type="submit" value="Rösta">
      <br><span id="if_delegate_vote"></span>
    </form>

  <?php endif; ?>

  </div>

  <p>
  <?php if($voteinfo['type'] == "prio-vote") : ?>
    <a href="index.php?type=vote&action=add_alternative&id=<?php echo $voteinfo['vote_id']; ?>">Lägg till ett alternativ till denna omröstning</a>
  <?php else : ?>
    <?php if(general_helpers::in_multiarray($votes_alternatives, "user_id", $_SESSION['id'])) : ?>
      <a href="index.php?type=vote&action=add_alternative&id=<?php echo $voteinfo['vote_id']; ?>">Dra tillbaka din kandidatur till denna omröstning</a>
    <?php else : ?>
      <a href="index.php?type=vote&action=add_alternative&id=<?php echo $voteinfo['vote_id']; ?>">Kandidera till denna omröstning</a>
    <?php endif; ?>
  <?php endif; ?>
  </p>

  <p>
  <?php if(isset($_SESSION['is_vote_admin'])) : ?>
    <a href="index.php?type=vote_admin&action=edit_alternatives&id=<?php echo $voteinfo['vote_id']; ?>">Valadministratör: Redigera alternativ för denna omröstning</a>
  <?php endif; ?>
  </p>

<?php endif; ?>






<script>
<?php if($_SESSION['acting_as_delegate']) : ?>
  <?php
    $delegate_ballot = db_delegate::get_ballot_for_vote($voteinfo['vote_id'], $delegate_id);
  ?>
  <?php if(!empty($delegate_ballot)) : ?>
    var vote = <?php echo json_encode($delegate_ballot); ?>;
    var prio_ranking_object = JSON.parse(vote.prio_ranking);

    var ul_support = document.getElementById("support-list");
    var ul_reject = document.getElementById("reject-list");

    for (var key in prio_ranking_object) {
      if (prio_ranking_object.hasOwnProperty(key)) {
 
        var li_element = document.getElementById(key);
        if(li_element != null){
          var li_content = li_element.innerHTML;
          li_element.parentNode.removeChild(li_element);

          var li = document.createElement("li");
          li.setAttribute("id", key);
          li.className = "sortable";

          if(prio_ranking_object[key] > 0){
            ul_support.appendChild(li);
          }
          else{
            ul_reject.appendChild(li);
          }

          document.getElementById(key).innerHTML = li_content;
        }
      }
    }

    if(vote.delegate_id != null){
      document.getElementById("if_delegate_vote").innerHTML += "<br>Din delegat <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> har röstat åt dig.";
    }
  <?php endif; ?>

<?php else : ?>
  list_of_votes.map(function (vote){
    if(vote.user_code == sessionStorage.active_user_code){
      var prio_ranking_object = JSON.parse(vote.prio_ranking);

      var ul_support = document.getElementById("support-list");
      var ul_reject = document.getElementById("reject-list");

      for (var key in prio_ranking_object) {
        if (prio_ranking_object.hasOwnProperty(key)) {
 
          var li_element = document.getElementById(key);
          if(li_element != null){
            var li_content = li_element.innerHTML;
            li_element.parentNode.removeChild(li_element);

            var li = document.createElement("li");
            li.setAttribute("id", key);
            li.className = "sortable";

            if(prio_ranking_object[key] > 0){
              ul_support.appendChild(li);
            }
            else{
              ul_reject.appendChild(li);
            }

            document.getElementById(key).innerHTML = li_content;
          }
        }
      }

      if(vote.delegate_id != null){
        document.getElementById("if_delegate_vote").innerHTML += "<br>Din delegat <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> har röstat åt dig.";
      }
    }
  });
<?php endif; ?>




var numberOfAlternatives = <?php echo $voteinfo['number_of_alternatives']; ?>;

var lists = {
    unsorted: $('.unsorted-box'),
    support: $('.support-box'),
    reject: $('.reject-box')
}, numberOfNonRejected = 0;

function onAfterUnsortedListPopulated() {
    lists.unsorted.find('li').each(function() {
          $(this).data('option-id', $(this).attr('id'));
    }).prepend('<span class="list-number"></span>');

    lists.support.find('li').each(function() {
          $(this).data('option-id', $(this).attr('id'));
    }).prepend('<span class="list-number"></span>');

    lists.reject.find('li').each(function() {
          $(this).data('option-id', $(this).attr('id'));
    }).prepend('<span class="list-number"></span>');
}

function setNumber(option, num) {
    $(option).find('.list-number').text(num ? num + '. ': '');
}

function getElementsWithoutDragged(list) {
    return list.find('li:not(".ui-sortable-helper")');    
}

function updateNumbersSupport() {
    var els = getElementsWithoutDragged(lists.support);
    
    els.each(function() {
        setNumber(this, els.index(this) + 1);
    });
}

function updateNumbersReject() {
    var els = getElementsWithoutDragged(lists.reject);
        
    els.each(function() {
        setNumber(this, numberOfNonRejected + els.index(this) + 1);
    });
}

onAfterUnsortedListPopulated();

$('.support-box, .unsorted-box, .reject-box').sortable({
    connectWith: '.prio-vote-box',
    sort: function(event, ui) {
        var list = $(ui.placeholder).parent()[0], num;
        
        numberOfNonRejected = getElementsWithoutDragged(lists.support.add(lists.unsorted)).length;
        
        switch (list) {
            case lists.support[0]:
                num = getElementsWithoutDragged(lists.support).index(ui.placeholder) + 1;
            break;
            case lists.reject[0]:
                num = numberOfNonRejected + getElementsWithoutDragged(lists.reject).index(ui.placeholder) + 1;
            break;
        }
        
        setNumber(ui.helper, num);
        updateNumbersSupport();
        updateNumbersReject();
    }
});

$('form').submit(function() {
  
    var data = {};
    
    lists.support.find('li').each(function() {
        data[$(this).data('option-id')] = numberOfAlternatives - $(this).index();
    });
    
    lists.reject.find('li').each(function() {
        data[$(this).data('option-id')] = -1 * ($(this).index() + 1);
    });
    
    encrypt_prio_ballot(data);
  
    return true;
});

numberOfNonRejected = getElementsWithoutDragged(lists.support.add(lists.unsorted)).length;
updateNumbersSupport();
updateNumbersReject();

</script>