
var console = (function()
{
	return {
		trace: [],
		log: function()
		{
			var line = '';
			for (var i = 0; i < arguments.length; i++)
			{
				line += typeof arguments[i] === 'string' ? arguments[i].replace('\n', '') : arguments[i];
				if (i < arguments.length - 1) line += ', ';
			}
			line += '\n';
			this.trace.push(line);
		}
	};
}());