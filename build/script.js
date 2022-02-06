let consoleDiv = document.getElementById('console')
let lastMsg = ''

out = function () {
  consoleDiv.innerText =
    consoleDiv.innerText + '\n' + Array.from(arguments).join(' ')
  lastMsg = Array.from(arguments).join(' ')
}

let runMex = Module.cwrap('runMex', 'void', ['string'])

function runAsm() {
  consoleDiv.innerText = ''
  try {
    runMex(window.editor.getValue())
    consoleDiv.className = 'success'
  } catch (e) {
    consoleDiv.innerText = lastMsg + '\n' + e.message
    consoleDiv.className = 'error'
  }
}
