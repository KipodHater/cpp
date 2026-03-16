import numpy as np
import matplotlib.pyplot as plt

# --------------------
# Constants (from your C++)
# --------------------
h = 1.82 - 0.35          # goal height relative to shooter
m = 0.21
dt = 0.01
g = 9.81
rho = 1.225
Cd = 0.2
radius = 0.09
PI = np.pi
simulation_time = 6.0
extra_height_from_hub = 0.2

# --------------------
# Physics
# --------------------
def compute_acceleration(vx, vy):
    v = np.hypot(vx, vy)
    if v == 0:
        return 0, -g

    drag_mag = rho * v * v * Cd * PI * radius * radius / 2
    ax = -drag_mag * vx / (v * m)
    ay = -g - drag_mag * vy / (v * m)
    return ax, ay


def simulate_shot(velocity, angle_deg, goal_distance, radial_velocity=0.0):
    angle = np.deg2rad(angle_deg)

    vx = velocity * np.cos(angle) + radial_velocity
    vy = velocity * np.sin(angle)

    x, y = 0.0, 0.0
    xs, ys = [x], [y]

    max_height = 0.0
    crossed_goal = False
    x_error = None

    t = 0.0
    while t < simulation_time and y > -1:
        ax, ay = compute_acceleration(vx, vy)

        vx += ax * dt
        vy += ay * dt
        x += vx * dt
        y += vy * dt

        xs.append(x)
        ys.append(y)
        max_height = max(max_height, y)

        # detect goal crossing
        if len(ys) >= 2:
            y0, y1 = ys[-2], ys[-1]
            if y0 >= h and y1 <= h and vy < 0:
                crossed_goal = True
                x_error = x - goal_distance
                break

        t += dt

    return np.array(xs), np.array(ys), crossed_goal, x_error, max_height


# --------------------
# Visualization
# --------------------
def visualize_shot(velocity, angle, goal_distance):
    xs, ys, hit, x_err, max_h = simulate_shot(
        velocity, angle, goal_distance
    )

    plt.figure(figsize=(10, 5))
    plt.plot(xs, ys, label="Trajectory", linewidth=2)

    # Goal
    plt.axhline(h, linestyle="--", color="green", label="Goal height")
    plt.axvline(goal_distance, linestyle="--", color="red", label="Goal plane")

    # Goal window
    plt.fill_between(
        [goal_distance - 0.05, goal_distance + 0.05],
        h - 0.2, h + 0.2,
        color="green", alpha=0.2, label="Goal window"
    )

    # Max height
    plt.scatter(xs[np.argmax(ys)], max_h, color="purple", zorder=5)
    plt.text(xs[np.argmax(ys)], max_h + 0.05,
             f"Max height: {max_h:.2f} m", ha="center")

    title = f"v={velocity} m/s, angle={angle}°"
    if hit:
        title += "  ✅ Crosses goal plane"
    else:
        title += "  ❌ Misses goal"

    plt.title(title)
    plt.xlabel("Distance (m)")
    plt.ylabel("Height (m)")
    plt.ylim(0, max(ys) + 0.5)
    plt.grid(True)
    plt.legend()
    plt.show()


# --------------------
# Example usage
# --------------------
if __name__ == "__main__":
    visualize_shot(
        velocity=10.2,
        angle=60,
        goal_distance=5.3
    )
# 7.50000,0.00000,10.00000,52.50000,41.92238