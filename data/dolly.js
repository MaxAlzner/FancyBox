var Dolly = (function ()
{
	'use strict';
	return function ()
	{
		this.Speed = 4.0;
		this.Spin = 10.0;
		this.OnUpdate = function ()
		{
			if (Key.w)
			{
				this.transform.position = Vec.add(this.transform.position, Vec.mul(this.transform.forward, this.Speed * Frame.deltaTime));
			}

			if (Key.s)
			{
				this.transform.position = Vec.sub(this.transform.position, Vec.mul(this.transform.forward, this.Speed * Frame.deltaTime));
			}

			if (Key.a)
			{
				this.transform.rotation.y += this.Spin * Frame.deltaTime;
			}

			if (Key.d)
			{
				this.transform.rotation.y -= this.Spin * Frame.deltaTime;
			}
		};
	};
}());