var TurnTable = (function()
{
	'use strict';
	return function ()
	{
		this.Delta = 0;
		this.OnStart = function()
		{
			Debug.Log('TurnTable started');
		};
		this.OnUpdate = function()
		{
			this.transform.rotation.y = this.Delta;
			this.Delta += 0.1;
		};
	};
}());