private function strDataHandler(event:SerialEvent):void {
	var rx_data:Array = event.strData.toUpperCase().split("");
	for each ( var chr:String in rx_data ){
		trace.debug( "received: " + chr );
		if( chr == "R" ){
			 browser.htmlLoader.reload();
		};
	}
}

/*つながったとき*/
private function connectHandler(event:Event):void {
	sport_state = SPORT_OPEN;
	setButtonLabel(sport_state);
	trace.debug("connectHandler: " + event);
}
private function connectErrorHandler(event:SerialErrorEvent):void {
	trace.debug("connectErrorHandler: " + event.message);
	closePort2();
}
/*ソケットがサーバーによって閉じられた時*/
private function closeHandler(event:Event):void {
	trace.debug("closeHandler: " + event);
}
/*サーバーへのコネンクションが一杯になりエラーが起こったとき*/
private function fullConnectionErrorHandler(event:SerialErrorEvent):void {
	trace.debug("fullConnectionErrorHandler: " + event);
}

/*エラーが来たとき*/
private function ioErrorHandler(event:IOErrorEvent):void {
	trace.debug("ioErrorHandler: " + event.text);
}

/*送信中の状態*/
private function progressHandler(event:ProgressEvent):void {
	trace.debug("progressHandler loaded:" + event.bytesLoaded + " total: " + event.bytesTotal);
}

/*セキュリティーエラーが起こったとき*/
private function securityErrorHandler(event:SecurityErrorEvent):void {
	trace.debug("securityErrorHandler: " + event);
}