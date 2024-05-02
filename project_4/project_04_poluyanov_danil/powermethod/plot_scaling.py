import subprocess
import re
import numpy as np
import plotly.graph_objects as go

def extract_time_from_output(file_path):
    times = {}
    with open(file_path, 'r') as file:
        for line in file:
            if "in" in line and "second(s) time" in line:
                match = re.search(r'in (\d+.\d+) second\(s\)', line)
                if match:
                    time = float(match.group(1))
                    proc_match = re.search(r'with (\d+) processors', line)
                    if proc_match:
                        procs = int(proc_match.group(1))
                        times[procs] = time
    return times

def plot_results(data, title, filename):
    fig = go.Figure()
    for key, val in data.items():
        sorted_items = sorted(val.items())  # sort by number of processors
        x, y = zip(*sorted_items)
        fig.add_trace(go.Scatter(x=x, y=y, mode='lines+markers', name=key))
    
    fig.update_layout(title=title,
                      xaxis_title='Number of Processors',
                      yaxis_title='Execution Time (seconds)',
                      legend_title='Test Type')
    fig.write_html(filename + '.html')

if __name__ == "__main__":
    strong_scaling = extract_time_from_output('powermethod_mpi-57160075.out')
    weak_scaling = extract_time_from_output('powermethod_mpi-57160075.out')
    
    plot_results({'Strong Scaling': strong_scaling, 'Weak Scaling': weak_scaling},
                 'MPI Power Method Scaling Analysis', 'mpi_scaling_analysis')
