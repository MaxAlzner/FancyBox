
function TestBehavior()
{
    this.Name = 'TestBehavior';
	this.Num = 0;
	this.Value = 0.5;
	this.Enabled = false;
	this.Transform = null;

	this.OnStart = function()
	{
		console.log('OnStart called');
	};

	this.OnEnd = function()
	{
		console.log('OnEnd called');
	};

	this.OnUpdate = function()
	{
		console.log('OnUpdate called');
		this.Num++;
		console.log('Number of times called', this.Num);
		//console.log('this', JSON.stringify(this));
	};
}
