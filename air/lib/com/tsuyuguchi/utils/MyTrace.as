package com.tsuyuguchi.utils{

import mx.formatters.DateFormatter;

public class MyTrace{
	public static const CRIT:int = 1;
	public static const ERROR:int = 2;
	public static const WARNING:int = 3;
	public static const NOTICE:int = 4;
	public static const INFO:int = 5;
	public static const DEBUG:int = 6;

	private var _out:Function = null;
	private var _level:int = 3;
	private var _formatter:DateFormatter = null;
	
	public function MyTrace( level:int, out:Function ):void {
		_out = out;
		setLevel( level );
		_formatter = new DateFormatter();
		_formatter.formatString = "YYYY/MM/DD HH:NN:SS";
	}

	public function setLevel( level:int ):void{
		_level = level;
	}

	private function _trace( level:int, msg:String ):void{
		if( level <= _level ){
			var now:Date = new Date();
			var prefix:String = "[" + _formatter.format(now) + "] ";
			_out( prefix + msg );
		}
	}
	
	public function crit( msg:String ):void{ _trace( 1, msg ); }
	public function error( msg:String ):void{ _trace( 2, msg ); }
	public function warning( msg:String ):void{ _trace( 3, msg ); }
	public function notice( msg:String ):void{ _trace( 4, msg ); }
	public function info( msg:String ):void{ _trace( 5, msg ); }
	public function debug( msg:String ):void{ _trace( 6, msg ); }

}

}