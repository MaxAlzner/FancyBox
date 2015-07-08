
function vec2_test()
{
	var v = new Vec2();
	console.log('Vec2 testing');
	if (v && typeof v === 'object') console.log('object exists');
	else console.log('object not found');
	if (v.magnitude && typeof v.magnitude === 'function') console.log('magnitude function exists');
	else console.log('magnitude not found');
	if (v.normalize && typeof v.normalize === 'function') console.log('normalize function exists');
	else console.log('normalize function not found');
	if (v.move && typeof v.move === 'function') console.log('move function exists');
	else console.log('move function not found');
	if (v.scale && typeof v.scale === 'function') console.log('scale function exists');
	else console.log('scale function not found');
	if (v.add && typeof v.add === 'function') console.log('add function exists');
	else console.log('add function not found');
	if (v.subtract && typeof v.subtract === 'function') console.log('subtract function exists');
	else console.log('subtract function not found');
	if (v.multiply && typeof v.multiply === 'function') console.log('multiply function exists');
	else console.log('multiply function not found');
	if (v.divide && typeof v.divide === 'function') console.log('divide function exists');
	else console.log('divide function not found');
	if (v.to && typeof v.to === 'function') console.log('to function exists');
	else console.log('to function not found');
	if (v.clamp && typeof v.clamp === 'function') console.log('clamp function exists');
	else console.log('clamp function not found');
	if (v.dot && typeof v.dot === 'function') console.log('dot function exists');
	else console.log('dot function not found');
}

function vec3_test()
{
	var v = new Vec3();
	console.log('Vec3 testing');
	if (v && typeof v === 'object') console.log('object exists');
	else console.log('object not found');
	if (v.magnitude && typeof v.magnitude === 'function') console.log('magnitude function exists');
	else console.log('magnitude not found');
	if (v.normalize && typeof v.normalize === 'function') console.log('normalize function exists');
	else console.log('normalize function not found');
	if (v.move && typeof v.move === 'function') console.log('move function exists');
	else console.log('move function not found');
	if (v.scale && typeof v.scale === 'function') console.log('scale function exists');
	else console.log('scale function not found');
	if (v.add && typeof v.add === 'function') console.log('add function exists');
	else console.log('add function not found');
	if (v.subtract && typeof v.subtract === 'function') console.log('subtract function exists');
	else console.log('subtract function not found');
	if (v.multiply && typeof v.multiply === 'function') console.log('multiply function exists');
	else console.log('multiply function not found');
	if (v.divide && typeof v.divide === 'function') console.log('divide function exists');
	else console.log('divide function not found');
	if (v.to && typeof v.to === 'function') console.log('to function exists');
	else console.log('to function not found');
	if (v.clamp && typeof v.clamp === 'function') console.log('clamp function exists');
	else console.log('clamp function not found');
	if (v.dot && typeof v.dot === 'function') console.log('dot function exists');
	else console.log('dot function not found');
	if (v.cross && typeof v.cross === 'function') console.log('cross function exists');
	else console.log('cross function not found');
	if (v.reflect && typeof v.reflect === 'function') console.log('reflect function exists');
	else console.log('reflect function not found');
	if (v.tangent && typeof v.tangent === 'function') console.log('tangent function exists');
	else console.log('tangent function not found');
}

function vec4_test()
{
	var v = new Vec4();
	console.log('Vec4 testing');
	if (v && typeof v === 'object') console.log('object exists');
	else console.log('object not found');
	if (v.magnitude && typeof v.magnitude === 'function') console.log('magnitude function exists');
	else console.log('magnitude not found');
	if (v.normalize && typeof v.normalize === 'function') console.log('normalize function exists');
	else console.log('normalize function not found');
	if (v.move && typeof v.move === 'function') console.log('move function exists');
	else console.log('move function not found');
	if (v.scale && typeof v.scale === 'function') console.log('scale function exists');
	else console.log('scale function not found');
	if (v.add && typeof v.add === 'function') console.log('add function exists');
	else console.log('add function not found');
	if (v.subtract && typeof v.subtract === 'function') console.log('subtract function exists');
	else console.log('subtract function not found');
	if (v.multiply && typeof v.multiply === 'function') console.log('multiply function exists');
	else console.log('multiply function not found');
	if (v.divide && typeof v.divide === 'function') console.log('divide function exists');
	else console.log('divide function not found');
	if (v.to && typeof v.to === 'function') console.log('to function exists');
	else console.log('to function not found');
	if (v.clamp && typeof v.clamp === 'function') console.log('clamp function exists');
	else console.log('clamp function not found');
	if (v.dot && typeof v.dot === 'function') console.log('dot function exists');
	else console.log('dot function not found');
	if (v.cross && typeof v.cross === 'function') console.log('cross function exists');
	else console.log('cross function not found');
	if (v.reflect && typeof v.reflect === 'function') console.log('reflect function exists');
	else console.log('reflect function not found');
	if (v.tangent && typeof v.tangent === 'function') console.log('tangent function exists');
	else console.log('tangent function not found');
	if (v.homogenize && typeof v.homogenize === 'function') console.log('homogenize function exists');
	else console.log('homogenize function not found');
}

function transform_test()
{
	var t = new Transform();
	console.log('Transform test');
	if (t && typeof t === 'object') console.log('object exists');
	else console.log('object not found');
	if (t.LookAt && typeof t.LookAt === 'function') console.log('LookAt function exists');
	else console.log('LookAt not found');
	if (t.Rotate && typeof t.Rotate === 'function') console.log('Rotate function exists');
	else console.log('Rotate not found');
	if (t.Translate && typeof t.Translate === 'function') console.log('Translate function exists');
	else console.log('Translate not found');
}

vec2_test();
vec3_test();
vec4_test();
transform_test();

var n = 0;

function foo()
{
	console.log('Hello World!');

	n++;
	console.log('value of n', n);

	/*if (this != undefined && this != null)
	{
		console.log('this found ' + JSON.stringify(this));
	}*/
	if (this.uv != undefined && this.uv != null)
	{
		if (this.uv instanceof Vec2) console.log('this uv is Vec2');
		else console.log('this uv is not an instanceof Vec2');
	}
	if (this.normal != undefined && this.normal != null)
	{
		if (this.normal instanceof Vec3) console.log('this normal is Vec3');
		else console.log('this normal is not an instanceof Vec3');
		this.normal = this.normal.normalize();
		if (this.normal instanceof Vec3) console.log('this normal is Vec3');
		else console.log('this normal is not an instanceof Vec3');
	}
	if (this.position != undefined && this.position != null)
	{
		if (this.position instanceof Vec4) console.log('this position is Vec4');
		else console.log('this position is not an instanceof Vec4');
		this.position = this.position.normalize();
		if (this.position instanceof Vec4) console.log('this position is Vec4');
		else console.log('this position is not an instanceof Vec4');
	}

	var t0 = new Transform();
	console.log('Creating Transform', JSON.stringify(t0));
	console.log('Space Enum', JSON.stringify(Space));

	this.blah = 0;

	//console.log('Foo has returned a value');

	//return param;
}
