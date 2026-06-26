import os

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from scipy.interpolate import griddata

# -------------------------
# Load CSV
# -------------------------
# If saved as file:
# df = pd.read_csv("your_file.csv")

# Or if pasting raw string:
from io import StringIO
print(os.getcwd())
csv_data = """robotics/shootingSolutions2.csv"""
df = pd.read_csv("robotics/shootingSolutions2.csv", encoding="utf-8-sig")
df.columns = df.columns.str.strip()
print(df.columns)

# -------------------------
# Extract axes
# -------------------------
x = df["distance"].values
y = df["radialVelocity"].values
z = df["solutionAngle"].values
heat = df["solutionVelocity"].values

# -------------------------
# Create grid for surface
# -------------------------
xi = np.linspace(min(x), max(x), 100)
yi = np.linspace(min(y), max(y), 100)
Xi, Yi = np.meshgrid(xi, yi)

# Interpolate angle surface
Zi = griddata((x, y), z, (Xi, Yi), method='linear')

# Interpolate velocity for coloring
Vi = griddata((x, y), heat, (Xi, Yi), method='linear')

# -------------------------
# Plot
# -------------------------
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Surface (TreeMap visualization)
surf = ax.plot_surface(
    Xi, Yi, Zi,
    facecolors=cm.viridis(
        (Vi - np.nanmin(Vi)) / (np.nanmax(Vi) - np.nanmin(Vi))
    ),
    linewidth=0,
    antialiased=True,
    alpha=0.7
)

# Scatter raw points
sc = ax.scatter(
    x, y, z,
    c=heat,
    cmap="viridis",
    s=30,
    edgecolor="black"
)

# Labels
ax.set_xlabel("Distance")
ax.set_ylabel("Radial Velocity")
ax.set_zlabel("Solution Angle")
ax.set_title("Double Interpolating TreeMap Visualization")

# Colorbar
mappable = cm.ScalarMappable(cmap="viridis")
mappable.set_array(heat)
fig.colorbar(mappable, ax=ax, label="Solution Velocity")

plt.show()