var TurnTable = (function() {
	'use strict';
	return function () {
		this.OnStart = function()
		{
			Debug.Log('TurnTable started');
			this.Delta = 0;
		};
		this.OnUpdate = function()
		{
			this.transform.rotation.y = this.Delta;
			this.Delta += 0.1;
		};
	};
}());