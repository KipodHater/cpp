import numpy as np
import matplotlib.pyplot as plt

# --------------------
# Constants (from your C++)
# --------------------
h = 1.82 - 0.66
m = 0.21
dt = 0.01
g = 9.81
rho = 1.225
Cd = 0.2
radius = 0.09
PI = np.pi
simulation_time = 6.0
extra_height_from_hub = 0.2

# Shooter model
hood_speed_ratio = 0.5
wheel_to_ball_ratio = 0.9
magnus_slope = 0.6
desired_hit_accuracy = 0.05


# --------------------
# Physics
# --------------------
def compute_acceleration(vx, vy, ball_spin):
    v = np.hypot(vx, vy)
    if v == 0:
        return 0, -g

    area = PI * radius * radius

    # ---- DRAG ----
    drag_mag = 0.5 * rho * Cd * area * v * v
    drag_x = -drag_mag * vx / v
    drag_y = -drag_mag * vy / v

    # ---- MAGNUS ----
    v_perp_x = -vy / v
    v_perp_y = vx / v

    spin_ratio = (ball_spin * radius) / v
    spin_ratio = min(spin_ratio, 0.6)

    Cl = magnus_slope * spin_ratio
    lift_mag = 0.5 * rho * area * v * v * Cl

    magnus_x = lift_mag * v_perp_x
    magnus_y = lift_mag * v_perp_y

    # ---- TOTAL ACCELERATION ----
    ax = (drag_x + magnus_x) / m
    ay = (-m * g + drag_y + magnus_y) / m

    return ax, ay


def simulate_shot(main_wheel_speed, angle_deg, goal_distance, radial_velocity=0.0):

    # ---- Wheel model ----
    v_main = main_wheel_speed
    v_hood = hood_speed_ratio * v_main

    # Ball exit velocity
    velocity = v_main * wheel_to_ball_ratio

    # Ball spin (rad/s)
    ball_spin = (v_main - v_hood) / (2.0 * radius)

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

        ax, ay = compute_acceleration(vx, vy, ball_spin)

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
def visualize_shot(main_wheel_speed, angle, goal_distance):
    xs, ys, hit, x_err, max_h = simulate_shot(
        main_wheel_speed, angle, goal_distance
    )

    plt.figure(figsize=(10, 5))
    plt.plot(xs, ys, label="Trajectory", linewidth=2)

    # Goal
    plt.axhline(h, linestyle="--", color="green", label="Goal height")
    plt.axvline(goal_distance, linestyle="--", color="red", label="Goal plane")

    # Goal window
    plt.fill_between(
        [goal_distance - desired_hit_accuracy,
         goal_distance + desired_hit_accuracy],
        h - 0.2, h + 0.2,
        color="green", alpha=0.2, label="Goal window"
    )

    # Max height
    plt.scatter(xs[np.argmax(ys)], max_h, color="purple", zorder=5)
    plt.text(xs[np.argmax(ys)], max_h + 0.05,
             f"Max height: {max_h:.2f} m", ha="center")

    title = f"Main wheel = {main_wheel_speed:.2f} m/s, angle = {angle}°"
    if hit and abs(x_err) < desired_hit_accuracy and \
       max_h >= h + extra_height_from_hub:
        title += "  ✅ Valid Shot"
    else:
        title += "  ❌ Miss"

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
        main_wheel_speed=5.90000,
        angle=85.5,
        goal_distance=0.3
        )