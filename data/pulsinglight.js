var PulsingLight = (function()
{
	'use strict';
	return function ()
	{
		this.Delta = 0;
		this.OnUpdate = function()
		{
			this.light.intensity = Math.sin(this.Delta) + 1;
			this.Delta += 0.02;
		};
	};
}());