<?php
	$itemXML   = '';

	$sites = array(
		array('ED089C2E405CE1D6', '字幕測試影片', 'youtube',
			'建立者：ypchentube', 'playlist', 'continue=0'),
	);

	foreach($sites as $site) {
		$itemTotal ++;
		$itemXML   .=
			"\t<item>\r\n" .
				"\t\t<title>" . ucfirst($site[4]) . ": " . $site[1] . "</title>\r\n" .
				"\t\t<link>" .
					$scriptsURLprefix . '/youtube.query.php?uid=' . $user_id .
						'&amp;input_method='  . urlencode($inputMethod) .
						'&amp;youtube_video=' . urlencode($localhostYoutubeVideo) .
						'&amp;yv_fmt_prefs='  . urlencode($youtubeVideoFmtPrefs) .
						'&amp;yv_cc_prefs='   . urlencode($youtubeVideoCCPrefs) .
						'&amp;yv_rmt_src='    . urlencode($youtubeVideoRemoteSource) .
						'&amp;query=1' .
							',' . $site[0] .
							',' . urlencode($site[1]) .
							',' . urlencode($site[4] . '|' . $site[5]) .
				"</link>\r\n" .
				"\t\t" . siteLogo($site[2]) . "\r\n" .
				"\t\t<note>" . $site[3] . "</note>\r\n" .
				"\t\t<mediaDisplay name=\"threePartsView\" />\r\n" .
			"\t</item>\r\n";
	}

	// local cc prefs: $fileLocalYoutubeVideoCCPrefs
	$sites = array(
		array('',
			'取消字幕嘗試載入', 'youtube',
			' -- 確認後將改為使用預設值 (' . $youtubeVideoCCPrefs . ')'),
		array('en',
			'字幕嘗試載入順序: 英文', 'youtube',
			' -- 確認後將設定為: en'),
		array('zh-Hant,zh-TW,zh-HK,en',
			'字幕嘗試載入順序: 正體中文、英文', 'youtube',
			' -- 確認後將設定為: zh-Hant,zh-TW,zh-HK,en'),
		array('zh-Hans,en',
			'字幕嘗試載入順序: 简体中文、英文', 'youtube',
			' -- 確認後將設定為: zh-Hans,en'),
		array('zh-Hant,zh-TW,zh-HK,zh-Hans,en',
			'字幕嘗試載入順序: 中文(正體優先)、英文', 'youtube',
			' -- 確認後將設定為: zh-Hant,zh-TW,zh-HK,zh-Hans,en'),
		array('zh-Hant,zh-TW,zh-HK,zh-Hans,en',
			'字幕嘗試載入順序: 中文(简体優先)、英文', 'youtube',
			' -- 確認後將設定為: zh-Hans,zh-Hant,zh-TW,zh-HK,en'),
	);

	foreach($sites as $site) {
		$itemTotal ++;
		$itemXML   .=
			"\t<item>\r\n" .
				"\t\t<title>" . $site[1] . "</title>\r\n" .
				"\t\t<onClick>\r\n" .
					"\t\t\tdataFile = \"" . $fileLocalYoutubeVideoCCPrefs . "\";\r\n" .
					"\t\t\tdataStr  = \"" . $site[0] . "\";\r\n" .
					"\t\t\twriteStringToFile(dataFile, dataStr);\r\n" .
					"\t\t\tlocalYoutubeVideoCCPrefs = readStringFromFile(dataFile);\r\n" .
					"\t\t\tif ((localYoutubeVideoCCPrefs == null) || (localYoutubeVideoCCPrefs == \"\")) {\r\n" .
						"\t\t\t\tmessage  = \" -- 已取消\";\r\n" .
					"\t\t\t}\r\n" .
					"\t\t\telse {\r\n" .
						"\t\t\t\tmessage  = \" -- 已設定為 {\" + localYoutubeVideoCCPrefs + \"}\";\r\n" .
					"\t\t\t}\r\n" .
					"\t\t\tredrawDisplay();\r\n" .
				"\t\t</onClick>\r\n" .
				"\t\t" . siteLogo($site[2]) . "\r\n" .
				"\t\t<note>\r\n" .
					"\t\t\t<script>\r\n" .
						"\t\t\t\tdataFile = \"" . $fileLocalYoutubeVideoCCPrefs . "\";\r\n" .
						"\t\t\t\tlocalYoutubeVideoCCPrefs = readStringFromFile(dataFile);\r\n" .
						"\t\t\t\tif ((localYoutubeVideoCCPrefs == null) || (localYoutubeVideoCCPrefs == \"\")) {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前本機無字幕順序設定 (正使用預設值: " . $youtubeVideoCCPrefs . ")\";\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\telse {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前嘗試載入字幕順序為: \" + localYoutubeVideoCCPrefs;\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\tnoteStr + \"" . $site[3] . "\";\r\n" .
					"\t\t\t</script>\r\n" .
				"\t\t</note>\r\n" .
				"\t\t<mediaDisplay name=\"threePartsView\" />\r\n" .
			"\t</item>\r\n";
	}

	$sites = array(
		array('input = doModalRss("rss_file://./etc/ypInput/keyboard.rss", "mediaDisplay", "search", 0);',
			'自行輸入字幕嘗試載入順序 / 本機輸入', 'youtube',
			' -- 逗號隔開勿空格, 常用代碼: en(英文), zh-Hant(正體), zh-Hans(简体), zh-TW(台灣), zh-HK(香港), ja(日本語), ko(韓語)'),
		array('input = getInput("Enter a keyword");',
			'自行輸入字幕嘗試載入順序 / 內建輸入', 'youtube',
			' -- 逗號隔開勿空格, 常用代碼: en(英文), zh-Hant(正體), zh-Hans(简体), zh-TW(台灣), zh-HK(香港), ja(日本語), ko(韓語)'),
		array('input = doModalRss("' . $inputMethod . '", "mediaDisplay", "search", 0);',
			'自行輸入字幕嘗試載入順序 / 線上輸入', 'youtube',
			' -- 逗號隔開勿空格, 常用代碼: en(英文), zh-Hant(正體), zh-Hans(简体), zh-TW(台灣), zh-HK(香港), ja(日本語), ko(韓語)'),
	);

	foreach($sites as $site) {
		$itemTotal ++;
		$itemXML   .=
			"\t<item>\r\n" .
				"\t\t<title>" . $site[1] . "</title>\r\n" .
				"\t\t<onClick>\r\n" .
					"\t\t\t" . $site[0] . "\r\n" .
					"\t\t\tif (input != null) {\r\n" .
					"\t\t\t\tdataFile = \"" . $fileLocalYoutubeVideoCCPrefs . "\";\r\n" .
					"\t\t\t\twriteStringToFile(dataFile, input);\r\n" .
					"\t\t\t\tlocalYoutubeVideoCCPrefs = readStringFromFile(dataFile);\r\n" .
					"\t\t\t\tif ((localYoutubeVideoCCPrefs == null) || (localYoutubeVideoCCPrefs == \"\")) {\r\n" .
						"\t\t\t\t\tmessage  = \" -- 已取消\";\r\n" .
					"\t\t\t\t}\r\n" .
					"\t\t\t\telse {\r\n" .
						"\t\t\t\t\tmessage  = \" -- 已設定為 {\" + localYoutubeVideoCCPrefs + \"}\";\r\n" .
					"\t\t\t\t}\r\n" .
					"\t\t\t\tredrawDisplay();\r\n" .
					"\t\t\t}\r\n" .
				"\t\t</onClick>\r\n" .
				"\t\t" . siteLogo($site[2]) . "\r\n" .
				"\t\t<note>\r\n" .
					"\t\t\t<script>\r\n" .
						"\t\t\t\tdataFile = \"" . $fileLocalYoutubeVideoCCPrefs . "\";\r\n" .
						"\t\t\t\tlocalYoutubeVideoCCPrefs = readStringFromFile(dataFile);\r\n" .
						"\t\t\t\tif ((localYoutubeVideoCCPrefs == null) || (localYoutubeVideoCCPrefs == \"\")) {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前本機無字幕順序設定 (正使用預設值: " . $youtubeVideoCCPrefs . ")\";\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\telse {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定: \" + localYoutubeVideoCCPrefs;\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\tnoteStr + \"" . $site[3] . "\";\r\n" .
					"\t\t\t</script>\r\n" .
				"\t\t</note>\r\n" .
				"\t\t<mediaDisplay name=\"threePartsView\" />\r\n" .
			"\t</item>\r\n";
	}

	// local cc fsize: $fileLocalCCFSize
	$sites = array(
		array('',
			'取消字幕字型大小設定', 'youtube',
			' -- 確認後將改為程式預設值: 24'),
		array('18',
			'字幕字型大小: 18', 'youtube',
			' -- 確認後將設定為: 18'),
		array('20',
			'字幕字型大小: 20', 'youtube',
			' -- 確認後將設定為: 20'),
		array('22',
			'字幕字型大小: 22', 'youtube',
			' -- 確認後將設定為: 22'),
		array('24',
			'字幕字型大小: 24', 'youtube',
			' -- 確認後將設定為: 24'),
		array('26',
			'字幕字型大小: 26', 'youtube',
			' -- 確認後將設定為: 26'),
		array('28',
			'字幕字型大小: 28', 'youtube',
			' -- 確認後將設定為: 28'),
	);

	foreach($sites as $site) {
		$itemTotal ++;
		$itemXML   .=
			"\t<item>\r\n" .
				"\t\t<title>" . $site[1] . "</title>\r\n" .
				"\t\t<onClick>\r\n" .
					"\t\t\tdataFile = \"" . $fileLocalCCFSize . "\";\r\n" .
					"\t\t\tdataStr  = \"" . $site[0] . "\";\r\n" .
					"\t\t\twriteStringToFile(dataFile, dataStr);\r\n" .
					"\t\t\tlocalCCFSize = readStringFromFile(dataFile);\r\n" .
					"\t\t\tif ((localCCFSize == null) || (localCCFSize == \"\")) {\r\n" .
						"\t\t\t\tmessage  = \" -- 已改為程式預設值: 24\";\r\n" .
					"\t\t\t}\r\n" .
					"\t\t\telse {\r\n" .
						"\t\t\t\tmessage  = \" -- 已設定字型大小為 {\" + localCCFSize + \"}\";\r\n" .
					"\t\t\t}\r\n" .
					"\t\t\tredrawDisplay();\r\n" .
				"\t\t</onClick>\r\n" .
				"\t\t" . siteLogo($site[2]) . "\r\n" .
				"\t\t<note>\r\n" .
					"\t\t\t<script>\r\n" .
						"\t\t\t\tdataFile = \"" . $fileLocalCCFSize . "\";\r\n" .
						"\t\t\t\tlocalCCFSize = readStringFromFile(dataFile);\r\n" .
						"\t\t\t\tif ((localCCFSize == null) || (localCCFSize == \"\")) {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定為程式預設值: 24\";\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\telse {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定字型大小為: \" + localCCFSize;\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\tnoteStr + \"" . $site[3] . "\";\r\n" .
					"\t\t\t</script>\r\n" .
				"\t\t</note>\r\n" .
				"\t\t<mediaDisplay name=\"threePartsView\" />\r\n" .
			"\t</item>\r\n";
	}

	$sites = array(
		array('input = doModalRss("rss_file://./etc/ypInput/keyboard.rss", "mediaDisplay", "search", 0);',
			'自行輸入字幕字型大小 / 本機輸入', 'youtube',
			' -- 格式為正整數, 例如: 24'),
		array('input = getInput("Enter a keyword");',
			'自行輸入字幕字型大小 / 內建輸入', 'youtube',
			' -- 格式為正整數, 例如: 24'),
		array('input = doModalRss("' . $inputMethod . '", "mediaDisplay", "search", 0);',
			'自行輸入字幕字型大小 / 線上輸入', 'youtube',
			' -- 格式為正整數, 例如: 24'),
	);

	foreach($sites as $site) {
		$itemTotal ++;
		$itemXML   .=
			"\t<item>\r\n" .
				"\t\t<title>" . $site[1] . "</title>\r\n" .
				"\t\t<onClick>\r\n" .
					"\t\t\t" . $site[0] . "\r\n" .
					"\t\t\tif (input != null) {\r\n" .
					"\t\t\t\tdataFile = \"" . $fileLocalCCFSize . "\";\r\n" .
					"\t\t\t\twriteStringToFile(dataFile, input);\r\n" .
					"\t\t\t\tlocalCCFSize = readStringFromFile(dataFile);\r\n" .
					"\t\t\t\tif ((localCCFSize == null) || (localCCFSize == \"\")) {\r\n" .
						"\t\t\t\t\tmessage  = \" -- 已改為程式預設值: 24\";\r\n" .
					"\t\t\t\t}\r\n" .
					"\t\t\t\telse {\r\n" .
						"\t\t\t\t\tmessage  = \" -- 已設定字型大小為 {\" + localCCFSize + \"}\";\r\n" .
					"\t\t\t\t}\r\n" .
					"\t\t\t\tredrawDisplay();\r\n" .
					"\t\t\t}\r\n" .
				"\t\t</onClick>\r\n" .
				"\t\t" . siteLogo($site[2]) . "\r\n" .
				"\t\t<note>\r\n" .
					"\t\t\t<script>\r\n" .
						"\t\t\t\tdataFile = \"" . $fileLocalCCFSize . "\";\r\n" .
						"\t\t\t\tlocalCCFSize = readStringFromFile(dataFile);\r\n" .
						"\t\t\t\tif ((localCCFSize == null) || (localCCFSize == \"\")) {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定為程式預設值: 24\";\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\telse {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定字型大小為: \" + localCCFSize;\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\tnoteStr + \"" . $site[3] . "\";\r\n" .
					"\t\t\t</script>\r\n" .
				"\t\t</note>\r\n" .
				"\t\t<mediaDisplay name=\"threePartsView\" />\r\n" .
			"\t</item>\r\n";
	}

	// local cc fcolor: $fileLocalCCFColor
	$sites = array(
		array('',
			'取消字幕字型顏色設定', 'youtube',
			' -- 確認後將改為程式預設值: 255:255:150 (淡黃)'),
		array('255:255:255',
			'字幕字型顏色: 255:255:255 (白)', 'youtube',
			' -- 確認後將設定為: 255:255:255 (白)'),
		array('255:255:150',
			'字幕字型顏色: 255:255:150 (淡黃)', 'youtube',
			' -- 確認後將設定為: 255:255:150 (淡黃)'),
		array('150:255:255',
			'字幕字型顏色: 150:255:255 (淡藍)', 'youtube',
			' -- 確認後將設定為: 150:255:255 (淡藍)'),
	);

	foreach($sites as $site) {
		$itemTotal ++;
		$itemXML   .=
			"\t<item>\r\n" .
				"\t\t<title>" . $site[1] . "</title>\r\n" .
				"\t\t<onClick>\r\n" .
					"\t\t\tdataFile = \"" . $fileLocalCCFColor . "\";\r\n" .
					"\t\t\tdataStr  = \"" . $site[0] . "\";\r\n" .
					"\t\t\twriteStringToFile(dataFile, dataStr);\r\n" .
					"\t\t\tlocalCCFColor = readStringFromFile(dataFile);\r\n" .
					"\t\t\tif ((localCCFColor == null) || (localCCFColor == \"\")) {\r\n" .
						"\t\t\t\tmessage  = \" -- 已改為程式預設值: 255:255:150 (淡黃)\";\r\n" .
					"\t\t\t}\r\n" .
					"\t\t\telse {\r\n" .
						"\t\t\t\tmessage  = \" -- 已設定字型顏色為 {\" + localCCFColor + \"}\";\r\n" .
					"\t\t\t}\r\n" .
					"\t\t\tredrawDisplay();\r\n" .
				"\t\t</onClick>\r\n" .
				"\t\t" . siteLogo($site[2]) . "\r\n" .
				"\t\t<note>\r\n" .
					"\t\t\t<script>\r\n" .
						"\t\t\t\tdataFile = \"" . $fileLocalCCFColor . "\";\r\n" .
						"\t\t\t\tlocalCCFColor = readStringFromFile(dataFile);\r\n" .
						"\t\t\t\tif ((localCCFColor == null) || (localCCFColor == \"\")) {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定為程式預設值: 255:255:150 (淡黃)\";\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\telse {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定字型顏色為: \" + localCCFColor;\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\tnoteStr + \"" . $site[3] . "\";\r\n" .
					"\t\t\t</script>\r\n" .
				"\t\t</note>\r\n" .
				"\t\t<mediaDisplay name=\"threePartsView\" />\r\n" .
			"\t</item>\r\n";
	}

	$sites = array(
		array('input = doModalRss("rss_file://./etc/ypInput/keyboard.rss", "mediaDisplay", "search", 0);',
			'自行輸入字幕字型顏色 / 本機輸入', 'youtube',
			' -- 格式為 R:G:B, 例如: 255:255:150'),
		array('input = getInput("Enter a keyword");',
			'自行輸入字幕字型顏色 / 內建輸入', 'youtube',
			' -- 格式為 R:G:B, 例如: 255:255:150'),
		array('input = doModalRss("' . $inputMethod . '", "mediaDisplay", "search", 0);',
			'自行輸入字幕字型顏色 / 線上輸入', 'youtube',
			' -- 格式為 R:G:B, 例如: 255:255:150'),
	);

	foreach($sites as $site) {
		$itemTotal ++;
		$itemXML   .=
			"\t<item>\r\n" .
				"\t\t<title>" . $site[1] . "</title>\r\n" .
				"\t\t<onClick>\r\n" .
					"\t\t\t" . $site[0] . "\r\n" .
					"\t\t\tif (input != null) {\r\n" .
					"\t\t\t\tdataFile = \"" . $fileLocalCCFColor . "\";\r\n" .
					"\t\t\t\twriteStringToFile(dataFile, input);\r\n" .
					"\t\t\t\tlocalCCFColor = readStringFromFile(dataFile);\r\n" .
					"\t\t\t\tif ((localCCFColor == null) || (localCCFColor == \"\")) {\r\n" .
						"\t\t\t\t\tmessage  = \" -- 已改為程式預設值: 255:255:150 (淡黃)\";\r\n" .
					"\t\t\t\t}\r\n" .
					"\t\t\t\telse {\r\n" .
						"\t\t\t\t\tmessage  = \" -- 已設定字型顏色為 {\" + localCCFColor + \"}\";\r\n" .
					"\t\t\t\t}\r\n" .
					"\t\t\t\tredrawDisplay();\r\n" .
					"\t\t\t}\r\n" .
				"\t\t</onClick>\r\n" .
				"\t\t" . siteLogo($site[2]) . "\r\n" .
				"\t\t<note>\r\n" .
					"\t\t\t<script>\r\n" .
						"\t\t\t\tdataFile = \"" . $fileLocalCCFColor . "\";\r\n" .
						"\t\t\t\tlocalCCFColor = readStringFromFile(dataFile);\r\n" .
						"\t\t\t\tif ((localCCFColor == null) || (localCCFColor == \"\")) {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定為程式預設值: 255:255:150 (淡黃)\";\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\telse {\r\n" .
							"\t\t\t\t\tnoteStr = \"目前設定字型顏色為: \" + localCCFColor;\r\n" .
						"\t\t\t\t}\r\n" .
						"\t\t\t\tnoteStr + \"" . $site[3] . "\";\r\n" .
					"\t\t\t</script>\r\n" .
				"\t\t</note>\r\n" .
				"\t\t<mediaDisplay name=\"threePartsView\" />\r\n" .
			"\t</item>\r\n";
	}
?>
