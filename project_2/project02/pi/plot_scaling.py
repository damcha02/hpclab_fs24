import subprocess as sp
import numpy as np
import plotly.graph_objects as go
import plotly.io as pio
import re

def plot_scaling_plotly(arr_time_average, title, yaxis_title, filename):
    fig = go.Figure()
    for method, times in arr_time_average.items():
        fig.add_trace(go.Scatter(x=list(times.keys()), y=list(times.values()), mode='lines+markers', name=method))
    
    fig.update_layout(title=title,
                      xaxis_title='Number of Threads',
                      yaxis_title=yaxis_title,
                      legend_title='Method')
    # Save plot in plots directory
    pio.write_html(fig, file=f'plots/{filename}.html')

def run_experiment(n_threads, exe_path, arg_str=''):
    env = {'OMP_NUM_THREADS': str(n_threads)}
    command = [exe_path] + ([arg_str] if arg_str else [])
    result = sp.run(command, env=env, stdout=sp.PIPE, text=True)
    output = result.stdout
    print(output)
    time_match = re.search(r'time = ([0-9.]+) secs', output)
    return float(time_match.group(1)) if time_match else None

if __name__ == "__main__":
    n_runs = 5
    n_threads_options = [2 ** i for i in range(8)]
    methods = ['pi_serial', 'pi_omp_critical', 'pi_omp_reduction']
    strong_scaling_times = {method: {} for method in methods}
    weak_scaling_times = {method: {} for method in methods}
    
    # Strong scaling
    for n_threads in n_threads_options:
        for method in methods:
            times = [run_experiment(n_threads, f"./{method}") for _ in range(n_runs)]
            strong_scaling_times[method][n_threads] = np.mean(times)
    
    plot_scaling_plotly(strong_scaling_times, 'Strong Scaling', 'Average Execution Time (sec)', 'strong_scaling')

    # Weak scaling
    for n_threads in n_threads_options:
        workload = 10000000 * n_threads  # Adjust workload per thread
        for method in methods:
            times = [run_experiment(n_threads, f"./{method}", str(workload)) for _ in range(n_runs)]
            weak_scaling_times[method][n_threads] = np.mean(times)

    plot_scaling_plotly(weak_scaling_times, 'Weak Scaling', 'Average Execution Time (sec)', 'weak_scaling')