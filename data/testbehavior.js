
Debug.Log('Running TestBehavior');
function TestBehavior()
{
	this.Name = 'TestBehavior';
	this.Num = 0;
	this.Value = 0.5;
	this.Enabled = false;

	this.OnStart = function()
	{
		Debug.Log('OnStart called');
	};

	this.OnEnd = function()
	{
		Debug.Log('OnEnd called');
	};

	this.OnUpdate = function()
	{
		Debug.Log('OnUpdate called');
		this.Num++;
		Debug.Log('Number of times called', this.Num);
	};
}
