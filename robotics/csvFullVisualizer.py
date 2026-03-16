import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider

# --------------------
# Field geometry
# --------------------
shooter_height = 0.66
hub_height = 1.82
hub_x = 0.0

# --------------------
# Physics constants
# --------------------
m = 0.21
dt = 0.01
g = 9.81
rho = 1.225
Cd = 0.2
radius = 0.09
PI = np.pi
simulation_time = 6.0

hood_speed_ratio = 0.5
wheel_to_ball_ratio = 0.9
magnus_slope = 0.6


# --------------------
# Load CSV
# --------------------
csv_path = "shootingSolutions2.csv"

data = pd.read_csv(csv_path)

distances = sorted(data["distance"].unique())
radial_velocities = sorted(data["radialVelocity"].unique())

distance_step = np.mean(np.diff(distances))


# --------------------
# Physics
# --------------------
def compute_acceleration(vx, vy, ball_spin):

    v = np.hypot(vx, vy)

    if v == 0:
        return 0, -g

    area = PI * radius * radius

    drag_mag = 0.5 * rho * Cd * area * v * v
    drag_x = -drag_mag * vx / v
    drag_y = -drag_mag * vy / v

    v_perp_x = -vy / v
    v_perp_y = vx / v

    spin_ratio = min((ball_spin * radius) / v, 0.6)

    Cl = magnus_slope * spin_ratio
    lift_mag = 0.5 * rho * area * v * v * Cl

    magnus_x = lift_mag * v_perp_x
    magnus_y = lift_mag * v_perp_y

    ax = (drag_x + magnus_x) / m
    ay = (-m * g + drag_y + magnus_y) / m

    return ax, ay


def simulate_shot(main_wheel_speed, angle_deg, radial_velocity, robot_distance):

    v_main = main_wheel_speed
    v_hood = hood_speed_ratio * v_main

    velocity = v_main * wheel_to_ball_ratio
    ball_spin = (v_main - v_hood) / (2.0 * radius)

    angle = np.deg2rad(angle_deg)

    vx = velocity * np.cos(angle) + radial_velocity
    vy = velocity * np.sin(angle)

    x = -robot_distance
    y = shooter_height

    xs = [x]
    ys = [y]

    t = 0

    while t < simulation_time and y > 0:

        ax, ay = compute_acceleration(vx, vy, ball_spin)

        vx += ax * dt
        vy += ay * dt

        x += vx * dt
        y += vy * dt

        xs.append(x)
        ys.append(y)

        # stop when reaching hub plane
        if x >= hub_x:
            break

        t += dt

    return np.array(xs), np.array(ys)


# --------------------
# Plot setup
# --------------------
fig, ax = plt.subplots(figsize=(12, 6))
plt.subplots_adjust(bottom=0.30)


def draw_trajectories(rv):

    ax.clear()

    max_height = 0

    # draw hub
    ax.scatter(hub_x, hub_height, color="red", s=120, label="Hub")

    for d in distances:

        row = data[
            (data.distance == d) &
            (data.radialVelocity == rv)
        ]

        if len(row) == 0:
            continue

        vel = float(row.solutionVelocity)
        ang = float(row.solutionAngle)

        xs, ys = simulate_shot(vel, ang, rv, d)

        max_height = max(max_height, max(ys))

        ax.plot(xs, ys, linewidth=2)

        # robot position
        ax.scatter(-d, shooter_height, color="black", s=30)

    # axis limits so everything is visible
    ax.set_xlim(-max(distances) - 0.5, 1)
    ax.set_ylim(0, max_height + 0.5)

    ax.set_title(f"Trajectories to Hub — Radial Velocity = {rv:.2f} m/s")

    ax.set_xlabel("Field X Position (m)")
    ax.set_ylabel("Height (m)")

    ax.grid(True)

    fig.canvas.draw_idle()


# initial draw
current_rv = radial_velocities[0]
draw_trajectories(current_rv)


# --------------------
# Slider
# --------------------
slider_ax = plt.axes([0.2, 0.15, 0.6, 0.03])

slider = Slider(
    slider_ax,
    "Radial Velocity Index",
    0,
    len(radial_velocities) - 1,
    valinit=0,
    valstep=1
)

# radial velocity text
velocity_text = plt.figtext(
    0.5,
    0.05,
    f"Radial Velocity: {radial_velocities[0]:.2f} m/s",
    ha="center",
    fontsize=12
)

# robot spacing text
distance_text = plt.figtext(
    0.5,
    0.01,
    f"Distance step between robot poses ≈ {distance_step:.3f} m",
    ha="center",
    fontsize=10
)


def update(val):

    idx = int(slider.val)
    rv = radial_velocities[idx]

    velocity_text.set_text(f"Radial Velocity: {rv:.2f} m/s")

    draw_trajectories(rv)


slider.on_changed(update)

plt.show()