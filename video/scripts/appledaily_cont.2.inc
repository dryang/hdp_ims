<channel>
<?php
	echo "<title>$myBaseName: 導覽選單</title>\r\n\r\n";

	if ($pass_check) {
		$siteURLprefix = '';
		foreach($videos as $video) {
			$title = trim(str_between($video, ');" >', '</a>'));
			$title = cleanFragments('/&#\d+/', convertUnicodePoints(strip_tags($title)));
			$data  = '';
			$link  = str_replace("'", '', str_replace(',', '|', trim(str_between($video, ' href="', '"'))));
			$image = '';
			$note  = '';
			$extra = '';

			if ((strpos($title, "最熱") !== false) || (strpos($title, "即時") !== false) || (strpos($title, "正妹") !== false)) {
				$pageStart = 1;
				$queryLevel = '.query.query';
			}
			else {
				$pageStart = 0;
				$queryLevel = '.query';
			}
			include('04_query.inc');
		}
	}
?>
</channel>
