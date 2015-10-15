var PulsingLight = (function ()
{
	'use strict';
	return function ()
	{
		this.Delta = 0;
		this.OnUpdate = function ()
		{
			this.light.intensity = (Math.sin(this.Delta) * 0.5) + 0.5;
			this.Delta += 0.02;
		};
	};
}());