

function confirmation()
{
	const params = new URLSearchParams(window.location.search)
	if(params.has('success')) 
	{
		alert("Operación exitosa");
	}	
	else if(params.has('failure')) 
	{
		alert("La operación falló");
	}
}