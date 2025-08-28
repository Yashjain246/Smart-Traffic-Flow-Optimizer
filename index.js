const outputLog = document.getElementById('output-log');
const form = document.getElementById('simulation-form');
const runButton = document.getElementById('runButton');

// This Module object is the magic. Emscripten will look for it.
// We are redirecting its print and printErr functions to our own function
// which will then write the output to the webpage.
var Module = {
    preRun: [],
    postRun: [],
    print: (function() {
        return function(text) {
            if (arguments.length > 1) {
                text = Array.prototype.slice.call(arguments).join(' ');
            }
            console.log(text);
            if (outputLog) {
                outputLog.textContent += text + "\n";
                // Auto-scroll to the bottom
                outputLog.scrollTop = outputLog.scrollHeight;
            }
        };
    })(),
    printErr: function(text) {
        if (arguments.length > 1) {
            text = Array.prototype.slice.call(arguments).join(' ');
        }
        console.error(text);
        if (outputLog) {
            outputLog.textContent += "[ERROR] " + text + "\n";
            outputLog.scrollTop = outputLog.scrollHeight;
        }
    },
};


// Listen for form submission
form.addEventListener('submit', (event) => {
    event.preventDefault();
    runSimulation();
});

function runSimulation() {
    outputLog.textContent = 'Initializing simulation...\n\n';
    runButton.disabled = true;
    runButton.textContent = 'Running...';

    // Get values from the form
    const numVehicles = document.getElementById('numVehicles').value;
    const simDuration = document.getElementById('simDuration').value;
    const startNode = document.getElementById('startNode').value;
    const endNode = document.getElementById('endNode').value;

    // These arguments will be passed to the main() function in C++
    const args = [
        numVehicles,
        simDuration,
        startNode,
        endNode
    ];

    // Call the main C++ function. The output will be piped to our `print` function above.
    // We wrap this in a timeout to allow the UI to update before the WASM blocks the main thread.
    setTimeout(() => {
        try {
            Module.callMain(args);
        } catch (e) {
            console.error(e);
            Module.printErr(e.toString());
        } finally {
            runButton.disabled = false;
            runButton.textContent = 'Run Simulation';
            Module.print("\n...Simulation finished.");
        }
    }, 50);
}

// This is an event listener that Emscripten will call when the WASM is ready.
window.addEventListener('load', () => {
    // The SmartTrafficModule function is created by module.js
    SmartTrafficModule(Module);
});
