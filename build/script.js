let consoleDiv = document.getElementById('console')
let consoleText = document.getElementById('console-text')
let lastMsg = ''

function format(s)
{
  return s.replaceAll('\t', '&nbsp;&nbsp;&nbsp;&nbsp;').replaceAll('\n', '<br>')
}

out = function () {
  consoleText.innerHTML =
  consoleText.innerHTML + '<br>' + format(Array.from(arguments).join(' '))
  lastMsg = Array.from(arguments).join(' ')
}

let runMex = Module.cwrap('runMex', 'void', ['string'])
let runMexDebug = Module.cwrap('runMexDebug', 'void', ['string'])

function runAsm() {
  consoleText.innerHTML = ''
  try {
    runMex(window.editor.getValue())
    consoleDiv.className = 'success'
  } catch (e) {
    consoleDiv.className = 'error'
    consoleText.innerHTML += '<br>' + format(e.message);
  }
}

function runAsmDebug() {
  consoleText.innerHTML = ''
  try {
    runMexDebug(window.editor.getValue());
    consoleDiv.className = 'success';
  } catch (e) {
    consoleDiv.className = 'error';
    consoleText.innerHTML += '<br>' + e.message;
  }
}
