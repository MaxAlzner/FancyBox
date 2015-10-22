var Dolly = (function ()
{
	'use strict';
	return function ()
	{
		this.Speed = 4.0;
		this.Spin = 10.0;
		this.OnUpdate = function ()
		{
			if (Key.w || Gamepad.sticks.left.y > 0.0)
			{
				this.transform.position = Vec.add(this.transform.position, Vec.mul(this.transform.forward, this.Speed * Frame.deltaTime));
			}

			if (Key.s || Gamepad.sticks.left.y < 0.0)
			{
				this.transform.position = Vec.sub(this.transform.position, Vec.mul(this.transform.forward, this.Speed * Frame.deltaTime));
			}

			if (Key.a || Gamepad.sticks.left.x < 0.0)
			{
				this.transform.rotation.y += this.Spin * Frame.deltaTime;
			}

			if (Key.d || Gamepad.sticks.left.x > 0.0)
			{
				this.transform.rotation.y -= this.Spin * Frame.deltaTime;
			}
		};
	};
}());