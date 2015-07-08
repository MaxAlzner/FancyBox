
var Space = (function()
{
	var num = {};
	Object.defineProperty(num, 'Self', {
		value: 0,
		configurable: false, 
		enumerable: true, 
		writable: false
	});
	Object.defineProperty(num, 'World', {
		value: 1,
		configurable: false, 
		enumerable: true, 
		writable: false
	});
	Object.seal(num);
	return num;
}());

function GameObject()
{

	Object.defineProperty(this, 'transform', {
		get: function()
		{
			return null;
		},
		configurable: false, 
		enumerable: true
	});

}

function Transform()
{
	Object.defineProperty(this, 'Position', {
		value: new Vec4(0.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});
	Object.defineProperty(this, 'EulerAngles', {
		value: new Vec3(0.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});
	Object.defineProperty(this, 'LossyScale', {
		value: new Vec3(1.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});

	Object.defineProperty(this, 'LocalPosition', {
		value: new Vec4(0.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});
	Object.defineProperty(this, 'LocalEulerAngles', {
		value: new Vec3(0.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});
	Object.defineProperty(this, 'LocalScale', {
		value: new Vec3(1.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});

	Object.defineProperty(this, 'Forward', {
		value: new Vec3(0.0, 0.0, 1.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});
	Object.defineProperty(this, 'Right', {
		value: new Vec3(1.0, 0.0, 0.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});
	Object.defineProperty(this, 'Up', {
		value: new Vec3(0.0, 1.0, 0.0),
		configurable: false, 
		enumerable: true, 
		writable: true
	});

	Object.defineProperty(this, 'Parent', {
		get: function()
		{
			return null;
		},
		configurable: false, 
		enumerable: true
	});
	Object.defineProperty(this, 'Root', {
		get: function()
		{
			return null;
		},
		configurable: false, 
		enumerable: true
	});

	Object.defineProperty(this, 'LookAt', {
		value: function(target, up)
		{
		},
		configurable: false, 
		enumerable: false, 
		writable: false
	});
	Object.defineProperty(this, 'Rotate', {
		value: function(axis, angle, space)
		{
		},
		configurable: false, 
		enumerable: false, 
		writable: false
	});
	Object.defineProperty(this, 'Translate', {
		value: function(axis, relativeTo)
		{
		},
		configurable: false, 
		enumerable: false, 
		writable: false
	});
	Object.seal(this);
}
