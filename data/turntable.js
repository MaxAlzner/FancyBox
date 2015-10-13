var TurnTable = (function ()
{
	'use strict';
	return function ()
	{
		this.Delta = 0;
		this.OnUpdate = function ()
		{
			this.transform.rotation = { x: this.transform.rotation.x, y: this.Delta, z: this.transform.rotation.z };
			this.Delta += 0.1;
		};
	};
}());