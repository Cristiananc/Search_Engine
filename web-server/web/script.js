function query_link(text_query) {
	const URL = "http://localhost:8080/query?text="+text_query;
  
	fetch(URL)
	  .then(function (response) {
		  return response.json();
	  })
	  .then(function (data) {
		  document.getElementById('output').innerHTML = data.res;
	  })
}

function query(){
	//Obtenho o texto digitado pelo usuário
	const text_query = document.getElementById("name").value;
	//URL que farei a query para o servidor
	const URL = "http://localhost:8080/query?text="+text_query;

	//Acesso o URL "escondido", sem atualizar a página atual
	fetch(URL)
		.then(function (response) {  //e "então", executo essa função com a resposta do URL
				return response.json();
			  })
		.then(function (data) {
				document.getElementById("output").innerHTML = data.res;
			  })
}