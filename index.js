import SmartTrafficModule from './module.js';

function addToPage(text) {
    const output = document.getElementById("output");
    output.textContent += text + "\n";
}

SmartTrafficModule({
    print: addToPage,
    printErr: addToPage
}).then((Module) => {
    addToPage("WASM module loaded!");

    // Example calls to your C++ functions:
    Module._startSimulation();
    Module._emergencyOverride();
    Module._stopSimulation();
});
