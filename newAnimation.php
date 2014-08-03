<?php
		$frames=$_GET['frames']; // muss als frames[]=111...000&frames[]=000...111&frames[]=...  übertragen werden
		$command = 'sudo /var/www/html/newAnimation.py '.$_GET['com'].' '.$_GET['rate'].' '.$_GET['speed'];
		foreach($frames as &$f){
				$command .= ' '.$f;
		}
		echo $command;
		echo nl2br(shell_exec(escapeshellcmd($command)));
?>
