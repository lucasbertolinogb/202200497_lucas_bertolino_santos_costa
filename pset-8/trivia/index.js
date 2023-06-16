<!DOCTYPE html>
<html lang="en">
<head>
    <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@500&display=swap" rel="stylesheet">
    <link href="styles.css" rel="stylesheet">
    <title>Trivia!</title>
    <script>
        // TODO: Add code to check answers to questions
        document.addEventListener('DOMContentLoaded', function(){
            let correto = document.querySelector('.correto');
            correto.addEventListener('click', function(){
                correto.style.backgroundColor = 'green';
                document.querySelector('#resposta1').innerHTML = 'Correto';
            });

            let incorretos = document.querySelectorAll('.incorreto');
            for (let i = 0; i < incorretos.length; i++){
                incorretos[i].addEventListener('click', function() {
                    incorretos[i].style.backgroundColor = 'red';
                    document.querySelector('#resposta1').innerHTML = 'Incorreto';
                });
            }

            document.querySelector('#checar').addEventListener('click', function(){
                let entrada = document.querySelector('input');
                if (entrada.value === 'Rússia') {
                    entrada.style.backgroundColor = 'green';
                    document.querySelector('#resposta2').innerHTML = 'Correto';
                } else {
                    entrada.style.backgroundColor = 'red';
                    document.querySelector('#resposta2').innerHTML = 'Incorreto';
                }
            });
        });
    </script>
</head>
<body>
    <div class="header">
        <h1>Trivia!</h1>
    </div>

    <div class="container">
        <div class="section">
            <h2>Part 1: Multiple Choice</h2>
            <hr>
            <h3>Quem é o presidente de: Brasil, EUA e Rússia</h3>
            <button id="1" onclick="alert('Correto')" class="correto">"Lula, Biden e Putin"</button>
            <button id="2" onclick="alert('Errado')" class="incorreto">"João Lourenço, Biden e Emmanuel Macron"</button>
            <button id="3" onclick="alert('Errado')" class="incorreto">"Pelé, LeBron James e Fiodor Dostoiévski."</button>

            <p id="resposta1"></p>
        </div>

        <div class="section">
            <h2>Part 2: Free Response</h2>
            <hr>

            <h3>Qual país é o maior em quilômetros totais?</h3>
            <input type="text" id="resposta-pais"></input>
            <button id="checar">Checar resposta</button>

            <p id="resposta2"></p>
        </div>
    </div>
</body>
</html>
