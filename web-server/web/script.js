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



function print_img(){
	const image_div = document.getElementById("image"); //Acesso a div que quero inserir a imagem
	const image_obj = document.createElement("img"); //Crio uma tag vazia <img></img>
	image_obj.src = "pokemon.jpeg"; //Altero o atributo "src", que é o endereço da imagem
	image_div.appendChild(image_obj); //Insiro a tag criada dentro da <div id ="image"></div>
}