
function Vec2(x_, y_)
{
	if (typeof x_ === 'number')
	{
		this.x = x_;
		if (typeof y_ === 'number')
		{
			this.y = y_;
		}
		else if (y_ instanceof Vec2 || y_ instanceof Vec3 || y_ instanceof Vec4)
		{
			this.y = y_.x;
		}
		else
		{
			this.y = this.x;
		}
	}
	else if (x_ instanceof Vec2 || x_ instanceof Vec3 || x_ instanceof Vec4)
	{
		this.x = x_.x;
		this.y = x_.y;
	}
	else
	{
		this.x = 0;
		this.y = 0;
	}
}

function Vec3(x_, y_, z_)
{
	if (typeof x_ === 'number')
	{
		this.x = x_;
		if (typeof y_ === 'number')
		{
			this.y = y_;
			if (typeof z_ === 'number')
			{
				this.z = z_;
			}
			else if (z_ instanceof Vec2 || z_ instanceof Vec3 || z_ instanceof Vec4)
			{
				this.z = z_.x;
			}
			else
			{
				this.z = this.y;
			}
		}
		else if (y_ instanceof Vec2 || y_ instanceof Vec3 || y_ instanceof Vec4)
		{
			this.y = y_.x;
			this.z = y_.y;
		}
		else
		{
			this.y = this.x;
			this.z = this.x;
		}
	}
	else if (x_ instanceof Vec2)
	{
		this.x = x_.x;
		this.y = x_.y;
		if (typeof y_ === 'number')
		{
			this.z = y_;
		}
		else if (y_ instanceof Vec2 || y_ instanceof Vec3 || y_ instanceof Vec4)
		{
			this.z = y_.x;
		}
		else
		{
			this.z = this.y;
		}
	}
	else if (x_ instanceof Vec3 || x_ instanceof Vec4)
	{
		this.x = x_.x;
		this.y = x_.y;
		this.z = x_.z;
	}
	else
	{
		this.x = 0;
		this.y = 0;
		this.z = 0;
	}
}

function Vec4(x_, y_, z_, w_)
{
	if (typeof x_ === 'number')
	{
		this.x = x_;
		if (typeof y_ === 'number')
		{
			this.y = y_;
			if (typeof z_ === 'number')
			{
				this.z = z_;
				if (typeof w_ === 'number')
				{
					this.w = w_;
				}
				else if (w_ instanceof Vec2 || w_ instanceof Vec3 || w_ instanceof Vec4)
				{
					this.w = w_.x;
				}
				else
				{
					this.w = this.z;
				}
			}
			else if (z_ instanceof Vec2 || z_ instanceof Vec3 || z_ instanceof Vec4)
			{
				this.z = z_.x;
				this.w = z_.y;
			}
			else
			{
				this.z = this.y;
				this.w = this.y;
			}
		}
		else if (y_ instanceof Vec2)
		{
			this.y = y_.x;
			this.z = y_.y;
			if (typeof z_ === 'number')
			{
				this.w = z_;
			}
			else if (z_ instanceof Vec2 || z_ instanceof Vec3 || z_ instanceof Vec4)
			{
				this.w = z_.x;
			}
			else
			{
				this.w = this.z;
			}
		}
		else if (y_ instanceof Vec3 || y_ instanceof Vec4)
		{
			this.y = x_.x;
			this.z = x_.y;
			this.w = x_.z;
		}
		else
		{
			this.y = this.x;
			this.z = this.x;
			this.w = this.x;
		}
	}
	else if (x_ instanceof Vec2)
	{
		this.x = x_.x;
		this.y = x_.y;
		if (typeof y_ === 'number')
		{
			this.z = y_;
			if (typeof z_ === 'number')
			{
				this.w = z_;
			}
			else if (z_ instanceof Vec2 || z_ instanceof Vec3 || z_ instanceof Vec4)
			{
				this.w = z_.x;
			}
			else
			{
				this.w = this.z;
			}
		}
		else if (y_ instanceof Vec2 || y_ instanceof Vec3 || y_ instanceof Vec4)
		{
			this.z = y_.x;
			this.w = y_.y;
		}
		else
		{
			this.z = this.y;
			this.w = this.y;
		}
	}
	else if (x_ instanceof Vec3)
	{
		this.x = x_.x;
		this.y = x_.y;
		this.z = x_.z;
		if (typeof y_ === 'number')
		{
			this.w = y_;
		}
		else if (y_ instanceof Vec2 || y_ instanceof Vec3 || y_ instanceof Vec4)
		{
			this.w = y_.x;
		}
		else
		{
			this.w = this.z;
		}
	}
	else if (x_ instanceof Vec4)
	{
		this.x = x_.x;
		this.y = x_.y;
		this.z = x_.z;
		this.w = x_.w;
	}
	else
	{
		this.x = 0;
		this.y = 0;
		this.z = 0;
		this.w = 0;
	}
}

Vec2.prototype.magnitude = function()
{
	return Math.sqrt((this.x * this.x) + (this.y * this.y));
}
Vec3.prototype.magnitude = function()
{
	return Math.sqrt((this.x * this.x) + (this.y * this.y) + (this.z * this.z));
}
Vec4.prototype.magnitude = function()
{
	return Math.sqrt((this.x * this.x) + (this.y * this.y) + (this.z * this.z) + (this.w * this.w));
}

Vec2.prototype.distance = function(other)
{
	if (other instanceof Vec2)
	{
		var v = this.subtract(other);
		return v.magnitude();
	}
	return 0;
}
Vec3.prototype.distance = function(other)
{
	if (other instanceof Vec3)
	{
		var v = this.subtract(other);
		return v.magnitude();
	}
	return 0;
}
Vec4.prototype.distance = function(other)
{
	if (other instanceof Vec4)
	{
		var v = this.subtract(other);
		return v.magnitude();
	}
	return 0;
}

Vec2.prototype.normalize = function()
{
	var m = this.magnitude();
	return new Vec2(this.x / m, this.y / m);
}
Vec3.prototype.normalize = function()
{
	var m = this.magnitude();
	return new Vec3(this.x / m, this.y / m, this.z / m);
}
Vec4.prototype.normalize = function()
{
	var m = this.magnitude();
	return new Vec4(this.x / m, this.y / m, this.z / m, this.w / m);
}

Vec2.prototype.move = function(x, y)
{
	if (isNaN(x)) return;
	if (isNaN(y)) y = x;

	this.x += x;
	this.y += y;
}
Vec3.prototype.move = function(x, y, z)
{
	if (isNaN(x)) return;
	if (isNaN(y)) y = x;
	if (isNaN(z)) z = y;

	this.x += x;
	this.y += y;
	this.z += z;
}
Vec4.prototype.move = function(x, y, z, w)
{
	if (isNaN(x)) return;
	if (isNaN(y)) y = x;
	if (isNaN(z)) z = y;
	if (isNaN(w)) w = z;

	this.x += x;
	this.y += y;
	this.z += z;
	this.w += w;
}

Vec2.prototype.scale = function(value)
{
	if (isNaN(value)) return;

	this.x *= value;
	this.y *= value;
}
Vec3.prototype.scale = function(value)
{
	if (isNaN(value)) return;

	this.x *= value;
	this.y *= value;
	this.z *= value;
}
Vec4.prototype.scale = function(value)
{
	if (isNaN(value)) return;

	this.x *= value;
	this.y *= value;
	this.z *= value;
	this.w *= value;
}

Vec2.prototype.add = function(other)
{
	if (other instanceof Vec2 || other instanceof Vec3 || other instanceof Vec4) return new Vec2(this.x + other.x, this.y + other.y);
	return undefined;
}
Vec3.prototype.add = function(other)
{
	if (other instanceof Vec3 || other instanceof Vec4) return new Vec3(this.x + other.x, this.y + other.y, this.z + other.z);
	return undefined;
}
Vec4.prototype.add = function(other)
{
	if (other instanceof Vec4) return new Vec4(this.x + other.x, this.y + other.y, this.z + other.z, this.w + other.w);
	return undefined;
}

Vec2.prototype.subtract = function(other)
{
	if (other instanceof Vec2 || other instanceof Vec3 || other instanceof Vec4) return new Vec2(this.x - other.x, this.y - other.y);
	return undefined;
}
Vec3.prototype.subtract = function(other)
{
	if (other instanceof Vec3 || other instanceof Vec4) return new Vec3(this.x - other.x, this.y - other.y, this.z - other.z);
	return undefined;
}
Vec4.prototype.subtract = function(other)
{
	if (other instanceof Vec4) return new Vec4(this.x - other.x, this.y - other.y, this.z - other.z, this.w - other.w);
	return undefined;
}

Vec2.prototype.multiply = function(other)
{
	if (other instanceof Vec2 || other instanceof Vec3 || other instanceof Vec4) return new Vec2(this.x * other.x, this.y * other.y);
	return undefined;
}
Vec3.prototype.multiply = function(other)
{
	if (other instanceof Vec3 || other instanceof Vec4) return new Vec3(this.x * other.x, this.y * other.y, this.z * other.z);
	return undefined;
}
Vec4.prototype.multiply = function(other)
{
	if (other instanceof Vec4) return new Vec4(this.x * other.x, this.y * other.y, this.z * other.z, this.w * other.w);
	return undefined;
}

Vec2.prototype.divide = function(other)
{
	if (other instanceof Vec2 || other instanceof Vec3 || other instanceof Vec4) return new Vec2(this.x / other.x, this.y / other.y);
	return undefined;
}
Vec3.prototype.divide = function(other)
{
	if (other instanceof Vec3 || other instanceof Vec4) return new Vec3(this.x / other.x, this.y / other.y, this.z / other.z);
	return undefined;
}
Vec4.prototype.divide = function(other)
{
	if (other instanceof Vec4) return new Vec4(this.x / other.x, this.y / other.y, this.z / other.z, this.w / other.w);
	return undefined;
}

Vec2.prototype.to = function(other)
{
	if (other instanceof Vec2 || other instanceof Vec3 || other instanceof Vec4) return new Vec2(other.x - this.x, other.y - this.y).normalize();
	return undefined;
}
Vec3.prototype.to = function(other)
{
	if (other instanceof Vec3 || other instanceof Vec4) return new Vec3(other.x - this.x, other.y - this.y, other.z - this.z).normalize();
	return undefined;
}
Vec4.prototype.to = function(other)
{
	if (other instanceof Vec4) return new Vec4(other.x - this.x, other.y - this.y, other.z - this.z, other.w - this.w).normalize();
	return undefined;
}

Vec2.prototype.clamp = function(min, max)
{
	if (isNaN(min)) min = 0.0;
	if (isNaN(max)) max = 1.0;

	return new Vec2(Math.max(Math.min(this.x, max), min), Math.max(Math.min(this.y, max), min));
}
Vec3.prototype.clamp = function(min, max)
{
	if (isNaN(min)) min = 0.0;
	if (isNaN(max)) max = 1.0;

	return new Vec2(Math.max(Math.min(this.x, max), min), Math.max(Math.min(this.y, max), min), Math.max(Math.min(this.z, max), min));
}
Vec4.prototype.clamp = function(min, max)
{
	if (isNaN(min)) min = 0.0;
	if (isNaN(max)) max = 1.0;

	return new Vec2(Math.max(Math.min(this.x, max), min), Math.max(Math.min(this.y, max), min), Math.max(Math.min(this.z, max), min), Math.max(Math.min(this.w, max), min));
}

Vec2.prototype.dot = function(other)
{
	if (other instanceof Vec2) return (this.x * other.x) + (this.y * other.y);
	return 0;
}
Vec3.prototype.dot = function(other)
{
	if (other instanceof Vec3) return (this.x * other.x) + (this.y * other.y) + (this.z * other.z);
	return 0;
}
Vec4.prototype.dot = function(other)
{
	if (other instanceof Vec4) return (this.x * other.x) + (this.y * other.y) + (this.z * other.z) + (this.w * other.w);
	return 0;
}

Vec3.prototype.cross = function(other)
{
	if (other instanceof Vec3 || other instanceof Vec4) return Vec3(
		(this.y * other.z) - (this.z * other.y), 
		(this.z * other.x) - (this.x * other.z), 
		(this.x * other.y) - (this.y * other.x)
		).normalize();
	return undefined;
}
Vec4.prototype.cross = function(other)
{
	if (other instanceof Vec3 || other instanceof Vec4) return Vec3(
		(this.y * other.z) - (this.z * other.y), 
		(this.z * other.x) - (this.x * other.z), 
		(this.x * other.y) - (this.y * other.x)
		).normalize();
	return undefined;
}

Vec3.prototype.reflect = function(other)
{
	if (other instanceof Vec3) other.scale(this.dot(other) * -2).subtract(this).normalize();
	return undefined;
}
Vec4.prototype.reflect = function(other)
{
	if (other instanceof Vec4) other.scale(this.dot(other) * -2).subtract(this).normalize();
	return undefined;
}

Vec3.prototype.tangent = function(other)
{
	if (other instanceof Vec3) other.scale(this.dot(other)).subtract(this).normalize();
	return undefined;
}
Vec4.prototype.tangent = function(other)
{
	if (other instanceof Vec4) other.scale(this.dot(other)).subtract(this).normalize();
	return undefined;
}

Vec4.prototype.homogenize = function()
{
	return Vec4(this.x / this.w, this.y / this.w, this.z / this.w, this.w / this.w);
}

Vec2.prototype.lerp = function(to, t)
{
	if (typeof t === 'number' && (other instanceof Vec2 || other instanceof Vec3 || other instanceof Vec4)) return ((to.subtract(this)).scale(t)).add(this);
	return undefined;
}
Vec3.prototype.lerp = function(to, t)
{
	if (typeof t === 'number' && (other instanceof Vec3 || other instanceof Vec4)) return ((to.subtract(this)).scale(t)).add(this);
	return undefined;
}
Vec4.prototype.lerp = function(to, t)
{
	if (typeof t === 'number' && other instanceof Vec4) return ((to.subtract(this)).scale(t)).add(this);
	return undefined;
}

Vec3.prototype.slerp = function(to, t)
{
	if (typeof t === 'number' && (other instanceof Vec3 || other instanceof Vec4))
	{
		t = Math.min(Math.max(t, 0.0), 1.0);
		((this.scale(1.0 - t)).add(to.scale(t))).normalize();
	}
	return undefined;
}
Vec3.prototype.slerp = function(to, t)
{
	if (typeof t === 'number' && other instanceof Vec4)
	{
		t = Math.min(Math.max(t, 0.0), 1.0);
		((this.scale(1.0 - t)).add(to.scale(t))).normalize();
	}
	return undefined;
}
