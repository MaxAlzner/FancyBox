var TurnTable = (function()
{
	'use strict';
	return function ()
	{
		this.Delta = 0;
		this.OnUpdate = function()
		{
			this.transform.ry = this.Delta;
			this.Delta += 0.1;
		};
	};
}());