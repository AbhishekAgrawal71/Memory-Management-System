from flask import Flask, render_template, request
import subprocess, os

app = Flask(__name__)

BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
BIN_DIR = os.path.join(BASE_DIR, "algorithms", "bin")

def run_executable(exe_name, input_str):
    exe_path = os.path.join(BIN_DIR, exe_name + ".exe")
    if not os.path.exists(exe_path):
        return f"Executable not found: {exe_path}"
    proc = subprocess.run([exe_path], input=input_str, capture_output=True, text=True)
    return proc.stdout or proc.stderr

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/run_allocation', methods=['POST'])
def run_allocation():
    n = int(request.form['number_of_blocks'])
    m = int(request.form['number_of_processes'])
    algo = request.form['algo_alloc']

    # Convert user inputs to integer lists
    block = list(map(int, request.form['blocks'].strip().split()))
    process = list(map(int, request.form['processes'].strip().split()))

    # Fix blocks list
    if len(block) >= n:
        blocks = block[:n]
    else:
        blocks = block + [0] * (n - len(block))

    # Fix processes list
    if len(process) >= m:
        processes = process[:m]
    else:
        processes = process + [0] * (m - len(process))

    # Prepare input for C exe
    input_data = f"{n}\n{' '.join(map(str, blocks))}\n{m}\n{' '.join(map(str, processes))}\n"

    exe_map = {"first": "alloc_firstfit", "best": "alloc_bestfit", "worst": "alloc_worstfit"}
    result = run_executable(exe_map[algo], input_data)

    return render_template(
    'result.html',
    title="Allocation Result",
    output=result,
    blocks=blocks
)



@app.route('/run_page', methods=['POST'])
def run_page():
    algo = request.form['algo_pr']
    frames = request.form['frames'].strip()
    refs = request.form['refs'].strip().split()
    input_data = f"{frames}\n{len(refs)}\n{' '.join(refs)}\n"
    exe_map = {"fifo":"pr_fifo","lru":"pr_lru","optimal":"pr_optimal"}
    result = run_executable(exe_map[algo], input_data)
    return render_template('result.html', title="Page Replacement Result", output=result)

if __name__ == "__main__":
    app.run(debug=True)
