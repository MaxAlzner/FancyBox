
var Vector = (function ()
	{
		'use strict';
		return {
			add: function (x, y, d)
			{
				x = typeof x === 'number' ? { x: x, y: x, z: x, w: x } : (x || {});
				y = typeof y === 'number' ? { x: y, y: y, z: y, w: y } : (y || {});
				d = d || {};
				d.x = (x.x ? x.x : 0) + (y.x ? y.x : 0);
				d.y = (x.y ? x.y : 0) + (y.y ? y.y : 0);
				if (x.z && y.z)
				{
					d.z = x.z + y.z;
				}
				
				if (x.w && y.w)
				{
					d.w = x.w + y.w;
				}
				
				return d;
			},
			sub: function (x, y, d)
			{
				x = typeof x === 'number' ? { x: x, y: x, z: x, w: x } : (x || {});
				y = typeof y === 'number' ? { x: y, y: y, z: y, w: y } : (y || {});
				d = d || {};
				d.x = (x.x ? x.x : 0) - (y.x ? y.x : 0);
				d.y = (x.y ? x.y : 0) - (y.y ? y.y : 0);
				if (x.z && y.z)
				{
					d.z = x.z - y.z;
				}
				
				if (x.w && y.w)
				{
					d.w = x.w - y.w;
				}
				
				return d;
			},
			mul: function (x, y, d)
			{
				x = typeof x === 'number' ? { x: x, y: x, z: x, w: x } : (x || {});
				y = typeof y === 'number' ? { x: y, y: y, z: y, w: y } : (y || {});
				d = d || {};
				d.x = (x.x ? x.x : 0) * (y.x ? y.x : 0);
				d.y = (x.y ? x.y : 0) * (y.y ? y.y : 0);
				if (x.z && y.z)
				{
					d.z = x.z * y.z;
				}
				
				if (x.w && y.w)
				{
					d.w = x.w * y.w;
				}
				
				return d;
			},
			div: function (x, y, d)
			{
				x = typeof x === 'number' ? { x: x, y: x, z: x, w: x } : (x || {});
				y = typeof y === 'number' ? { x: y, y: y, z: y, w: y } : (y || {});
				d = d || {};
				d.x = (x.x ? x.x : 0) / (y.x ? y.x : 0);
				d.y = (x.y ? x.y : 0) / (y.y ? y.y : 0);
				if (x.z && y.z)
				{
					d.z = x.z / y.z;
				}
				
				if (x.w && y.w)
				{
					d.w = x.w / y.w;
				}
				
				return d;
			},
			mag: function (v, d)
			{
				v = v || {};
				var x = v.x || 0, y = v.y || 0, z = v.z || 0, w = v.w || 0;
				d = v ? Math.sqrt((x * x) + (y * y) + (z * z) + (w * w)) : 0;
				return d;
			},
			normalize: function (v, d)
			{
				d = Vector.mul(v, Vector.mag(v));
				return d;
			},
			cross: function (x, y, d)
			{
				x = x || {};
				y = y || {};
				var x = x.x || 0, y = x.y || 0, z = x.z || 0, r = y.x || 0, g = y.y || 0, b = y.z || 0;
				d = {
					x: (y * b) - (z * g),
					y: (z * r) - (x * b),
					z: (x * g) - (y * r)
				};
				return d;
			}
		};
	} ());

var Vec = Vector;