const runButton = document.getElementById('runButton');
const outputLog = document.getElementById('output-log');
const form = document.getElementById('simulation-form');

let Module = {
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
        }
    },
    canvas: (function() {
        return document.getElementById('canvas');
    })(),
    setStatus: function(text) {
        // Status updates can be handled here if needed
    },
    totalDependencies: 0,
    monitorRunDependencies: function(left) {
        // Dependency monitoring can be handled here
    }
};

form.addEventListener('submit', (event) => {
    event.preventDefault();
    runSimulation();
});

function runSimulation() {
    outputLog.textContent = 'Starting simulation...\n\n';

    const numNodes = document.getElementById('numNodes').value;
    const numEdges = document.getElementById('numEdges').value;
    const edgesData = document.getElementById('edgesData').value.trim().split('\n').join(' ');
    const startNode = document.getElementById('startNode').value;
    const emergencyNode = document.getElementById('emergencyNode').value;

    const args = [
        numNodes,
        numEdges,
        ...edgesData.split(' '),
        startNode,
        emergencyNode
    ];

    Module.callMain(args);
}