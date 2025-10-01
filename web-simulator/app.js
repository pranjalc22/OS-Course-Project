let jobs = [];

function addJobInput() {
    const jobInputs = document.getElementById('jobInputs');
    const idx = jobInputs.children.length + 1;
    const row = document.createElement('div');
    row.className = 'job-row';
    row.innerHTML = `
        <label>Job ${idx}:</label>
        <input type="number" min="1" placeholder="Burst Time" required>
        <input type="number" min="0" placeholder="Arrival Time" required>
        <button type="button" onclick="this.parentElement.remove()">Remove</button>
    `;
    jobInputs.appendChild(row);
}

function getJobsFromInputs() {
    const jobRows = document.querySelectorAll('#jobInputs .job-row');
    jobs = [];
    jobRows.forEach((row, i) => {
        const burst = parseInt(row.children[1].value);
        const arrival = parseInt(row.children[2].value);
        if (!isNaN(burst) && !isNaN(arrival)) {
            jobs.push({ pid: i+1, burst_time: burst, arrival_time: arrival, remaining_time: burst });
        }
    });
}

function runSimulation(e) {
    e.preventDefault();
    getJobsFromInputs();
    if (jobs.length === 0) {
        alert('Please add at least one job with valid details.');
        return;
    }
    simulateMemory();
    simulateScheduling();
    showResults();
}

document.getElementById('jobForm').addEventListener('submit', runSimulation);

function simulateMemory() {
    // Simple paging: each job gets a frame
    jobs.forEach((job, i) => {
        job.frame = i;
    });
}

function simulateScheduling() {
    // Simple FCFS scheduling
    jobs.sort((a, b) => a.arrival_time - b.arrival_time);
    let time = 0;
    jobs.forEach(job => {
        job.start_time = Math.max(time, job.arrival_time);
        job.finish_time = job.start_time + job.burst_time;
        job.turnaround = job.finish_time - job.arrival_time;
        job.waiting = job.start_time - job.arrival_time;
        time = job.finish_time;
    });
}

function showResults() {
    // Process Table
    let tableHtml = `<table border="1" cellpadding="6"><tr><th>PID</th><th>Burst</th><th>Arrival</th><th>Start</th><th>Finish</th><th>Turnaround</th><th>Waiting</th></tr>`;
    jobs.forEach(job => {
        tableHtml += `<tr><td>${job.pid}</td><td>${job.burst_time}</td><td>${job.arrival_time}</td><td>${job.start_time}</td><td>${job.finish_time}</td><td>${job.turnaround}</td><td>${job.waiting}</td></tr>`;
    });
    tableHtml += `</table>`;
    document.getElementById('processTable').innerHTML = tableHtml;

    // Memory Map
    let memHtml = `<h3>Memory Map</h3><ul>`;
    jobs.forEach(job => {
        memHtml += `<li>Frame ${job.frame}: Job PID=${job.pid}</li>`;
    });
    memHtml += `</ul>`;
    document.getElementById('memoryMap').innerHTML = memHtml;

    // Scheduling Order
    let schedHtml = `<h3>Scheduling Order</h3><ol>`;
    jobs.forEach(job => {
        schedHtml += `<li>Job PID=${job.pid} (Start: ${job.start_time}, Finish: ${job.finish_time})</li>`;
    });
    schedHtml += `</ol>`;
    document.getElementById('schedulingOrder').innerHTML = schedHtml;

    // Plotly Graphs
    plotCharts();
}

function plotCharts() {
    // Gantt Chart for Scheduling
    let data = jobs.map(job => ({
        x: [job.start_time, job.finish_time],
        y: ["Job " + job.pid, "Job " + job.pid],
        mode: 'lines',
        line: { width: 20 },
        name: 'Job ' + job.pid
    }));
    let layout = {
        title: 'Scheduling Gantt Chart',
        xaxis: { title: 'Time' },
        yaxis: { title: 'Jobs', type: 'category' },
        showlegend: false,
        height: 400
    };
    Plotly.newPlot('charts', data, layout);
}

// Add one job input by default
addJobInput();
