var PulsingLight = (function ()
{
	'use strict';
	return function ()
	{
		this.Delta = 0;
		this.OnUpdate = function ()
		{
			var t = (Math.sin(this.Delta) + 1) * 0.5;
			this.light.intensity = t;
			this.Delta += 0.02;
		};
	};
}());