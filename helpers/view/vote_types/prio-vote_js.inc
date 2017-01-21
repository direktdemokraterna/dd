<script>
  var you_promoted = "Du stöder: ";
  var you_demoted = "Du motarbetar: ";
  var you_voted_abstain = "Du har röstat avstår.";
  var you_voted_yourself = "Du har personligen lagt denna röst";
  var your_delegate = "Din delegat";
  var voted_for_you = "har röstat åt dig.";

<?php if($_SESSION['delegate_id']) : ?>
  <?php if(!empty($delegate_ballot) && $delegate_ballot['ballot'] != "abstain") : ?>
    var vote = <?php echo json_encode($delegate_ballot); ?>;
    var prio_ranking_object = JSON.parse(vote.ballot);
    var ul_support = document.getElementById("support-list");
    var ul_reject = document.getElementById("reject-list");
    var sorted_prio_ranking=[];
    for(var key in prio_ranking_object)
        if(prio_ranking_object.hasOwnProperty(key))
            sorted_prio_ranking.push([key, prio_ranking_object[key]]); 

    // sort items by value
    sorted_prio_ranking.sort(function(a, b)
    {
      return b[1]-a[1]; // compare numbers
    });

      for(var i = 0; i < sorted_prio_ranking.length; i++) {
        var key = sorted_prio_ranking[i][0];
        var value = sorted_prio_ranking[i][1];
        var li_element = document.getElementById(key);
        if(li_element != null){
          var li_content = li_element.innerHTML;
          li_element.parentNode.removeChild(li_element);
          var li = document.createElement("li");
          li.setAttribute("id", key);
          li.className = "sortable";
          if(value)
            ul_support.appendChild(li);
          else
            ul_reject.appendChild(li);
          document.getElementById(key).innerHTML = li_content;
        }
    }

    if(vote.delegate_id != null)
      document.getElementById("if_delegate_vote").innerHTML += "<br>" + your_delegate + " <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> " + voted_for_you;
  <?php endif; ?>

<?php else : ?>
  if (acting_as_delegate ? false : true)
    ballots_to_count.map(function (ballot){
      if(ballot.user_code == sessionStorage.user_code){
        var user_vote_box = document.getElementById("user_vote_box");
        output_prio_vote(user_vote_box, ballot);
        if(ballot.delegate_id == null){
          user_vote_box.innerHTML += you_voted_yourself;
          document.getElementById("white_vote").style.display = "inline-block";
        }
        else
          user_vote_box.innerHTML = your_delegate + " <a href='index.php?type=vote&action=view_delegate&id=" + ballot.delegate_id + "'>" + ballot.delegate_name + "</a> " + voted_for_you;
      }
    });
<?php endif; ?>
var numberOfAlternatives = <?php echo $voteinfo['number_of_alternatives']; ?>;
var prio_type = "";
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

function prio_abstain(){
  prio_type = "abstain";
}

function prio_cancel(){
  prio_type = "cancel";
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
    if(prio_type === "abstain"){
      var data = {};
      encrypt_prio_ballot(data);
    }
    else if(prio_type === "cancel")
      encrypt_prio_ballot("cancel");
    else{
      var data = {};
      lists.support.find('li').each(function() {
        data[$(this).data('option-id')] = numberOfAlternatives - $(this).index();
      });
      lists.reject.find('li').each(function() {
        data[$(this).data('option-id')] = -1 * ($(this).index() + 1);
      });
      encrypt_prio_ballot(data);
    }
    return true;
});

numberOfNonRejected = getElementsWithoutDragged(lists.support.add(lists.unsorted)).length;
updateNumbersSupport();
updateNumbersReject();

</script>