import pandas as pd
import matplotlib.pyplot as plt

df_k26 = pd.read_csv("results/summary.csv")
df_k32 = pd.read_csv("results/large_summary.csv")
df_k26["K"] = 26
df_k32["K"] = 32

if "Memory(MB)" in df_k32.columns:
    df_k32.rename(columns={"Memory(MB)": "Memory"}, inplace=True)

def plot_k26_io(io_val):
    subset = df_k26[df_k26["IOThreads"] == io_val]
    fig, ax = plt.subplots()
    for mem in sorted(subset["Memory"].unique()):
        mem_data = subset[subset["Memory"] == mem]
        ax.plot(mem_data["Threads"], mem_data["Throughput(MH/s)"], marker='o', label=f"{mem} MB")
    ax.set_title(f"K=26, IOThreads={io_val}")
    ax.set_xlabel("Compute Threads")
    ax.set_ylabel("Throughput (MH/s)")
    ax.legend(title="Memory Size")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"plot_k26_io{io_val}.png")
    plt.close()

def plot_k32():
    subset = df_k32[(df_k32["Threads"] == 24) & (df_k32["IOThreads"] == 1)]
    fig, ax = plt.subplots()
    ax.plot(subset["Memory"], subset["Throughput(MH/s)"], marker='o', color='purple')
    ax.set_title("K=32, Threads=24, IOThreads=1")
    ax.set_xlabel("Memory (MB)")
    ax.set_ylabel("Throughput (MH/s)")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig("plot_k32.png")
    plt.close()

plot_k26_io(1)
plot_k26_io(2)
plot_k26_io(4)
plot_k32()
