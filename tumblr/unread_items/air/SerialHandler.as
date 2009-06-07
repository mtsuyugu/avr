private function strDataHandler(event:SerialEvent):void {
	var rx_data:Array = event.strData.toUpperCase().split("");
	for each ( var chr:String in rx_data ){
		trace.debug( "received: " + chr );
		if( chr == "R" ){
			 browser.htmlLoader.reload();
		};
	}
}

/*�Ȃ������Ƃ�*/
private function connectHandler(event:Event):void {
	sport_state = SPORT_OPEN;
	setButtonLabel(sport_state);
	trace.debug("connectHandler: " + event);
}
private function connectErrorHandler(event:SerialErrorEvent):void {
	trace.debug("connectErrorHandler: " + event.message);
	closePort2();
}
/*�\�P�b�g���T�[�o�[�ɂ���ĕ���ꂽ��*/
private function closeHandler(event:Event):void {
	trace.debug("closeHandler: " + event);
}
/*�T�[�o�[�ւ̃R�l���N�V��������t�ɂȂ�G���[���N�������Ƃ�*/
private function fullConnectionErrorHandler(event:SerialErrorEvent):void {
	trace.debug("fullConnectionErrorHandler: " + event);
}

/*�G���[�������Ƃ�*/
private function ioErrorHandler(event:IOErrorEvent):void {
	trace.debug("ioErrorHandler: " + event.text);
}

/*���M���̏��*/
private function progressHandler(event:ProgressEvent):void {
	trace.debug("progressHandler loaded:" + event.bytesLoaded + " total: " + event.bytesTotal);
}

/*�Z�L�����e�B�[�G���[���N�������Ƃ�*/
private function securityErrorHandler(event:SecurityErrorEvent):void {
	trace.debug("securityErrorHandler: " + event);
}