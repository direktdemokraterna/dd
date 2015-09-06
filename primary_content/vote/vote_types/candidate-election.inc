<?php if($voteinfo['status'] == "active" || $voteinfo['status'] == "continuous" || ($voteinfo['status'] == "del_ended" && !$_SESSION['delegate_id'])) : ?>

  Rangordna kandidaterna:<br>
  
  <form method="post" action="" class="prio-vote">
    <input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">
    <input type="hidden" name="ballot" id="ballot" value="">

    <ul class="prio-vote-box support-box" id="support-list"></ul>

    <ul class="prio-vote-box unsorted-box">

    <?php
      $votes_alternatives = db_vote::get_candidates_for_vote($voteinfo['vote_id']);
    ?>

    <?php foreach($votes_alternatives as $row) : ?>
      <li class="sortable" id="<?php echo $row['id']; ?>"><span title="<?php echo $row['description']; ?>"><?php echo $row['user_name']; ?></span></li>
    <?php endforeach; ?>

    </ul>

    <ul class="prio-vote-box reject-box" id="reject-list"></ul>

    <input type="submit" value="R�sta">
    <br><span id="if_delegate_vote"></span>
  </form>

  </div>

  <div>
  <p>
  <?php if(general_helpers::in_multiarray($votes_alternatives, "user_id", $_SESSION['id'])) : ?>
    <a href="index.php?type=vote&action=add_alternative&id=<?php echo $voteinfo['vote_id']; ?>">Dra tillbaka din kandidatur till denna omr�stning</a>
  <?php else : ?>
    <a href="index.php?type=vote&action=add_alternative&id=<?php echo $voteinfo['vote_id']; ?>">Kandidera till denna omr�stning</a>
  <?php endif; ?>
  </p>

  <p>
  <?php if(isset($_SESSION['is_vote_admin'])) : ?>
    <a href="index.php?type=vote_admin&action=edit_alternatives&id=<?php echo $voteinfo['vote_id']; ?>">Valadministrat�r: Redigera alternativ f�r denna omr�stning</a>
  <?php endif; ?>
  </p>

<?php endif; ?>