#include<bits/stdc++.h>
using namespace std;

double h = 1.84; // 2.64 - shooter height
double m = 0.26;
double dt = 0.001; // s
double velocityRobustnessCoefficient = 1;
double angleRobustnessCoefficient = 1;
double velocityInaccuracy = 0.3; // mps
double angleInaccuracy = 2; // deg
double g = 9.81;
double rho = 1.225;
double dragCoefficient = 0.25;
double r = 0.09;
double epsilon = 0.1;
const double PI = 3.14159;
// vector<vector<pair<double,double>>> paths;
vector<vector<double>> solutions;

struct SimRes {
    bool hit;
    double xError;
    double maxHeight;
};

void saveToCSV(const vector<vector<double>>& solutions, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }

    // header
    file << "distance,radialVelocity,solutionVelocity,solutionAngle,robustness\n";

    file << fixed << setprecision(5);
    for (const auto& row : solutions) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i + 1 < row.size()) file << ",";
        }
        file << "\n";
    }

    file.close();
}

bool hit(pair<double, double> pos, double d) {
    return math.hypot(d - pos.first, h - pos.second) <= epsilon;
}

pair<double, double> computeForces(pair<double, double> vel) {
    pair<double, double> fg = {0, -m*g};
    double velMag = hypot(vel.first, vel.second);
    if (velMag == 0) return fg; // prevent NaN
    pair<double, double> vHat = {vel.first / velMag, vel.second / velMag};
    double dragMag = rho * velMag * velMag * dragCoefficient * r * r * PI / 2;
    pair<double, double> fd = {-dragMag * vHat.first, -dragMag * vHat.second};
    // fm
    return {fg.first + fd.first, fg.second + fd.second};
}

SimRes simulate(double velMag, double velAngle, double radialVel, double d) {
    pair<double, double> pos = {0,0};
    pair<double, double> vel = {velMag* cos(velAngle * PI / 180) + radialVel, velMag* sin(velAngle * PI / 180)};
    double maxHeight = -1.0;
    pair<double, double> lastPose = {0, 0};
    double xError = -10;
    // vector<pair<double, double>> path;

   for(double t = 0; t < 6; t += dt) { 
        lastPose = pos;
        pair<double, double> a = computeForces(vel);
        a = {a.first / m, a.second/m};
        vel.first += a.first * dt;
        vel.second += a.second * dt;
        pos.first += vel.first * dt;
        pos.second += vel.second * dt;
        maxHeight = max(maxHeight, pos.second);
        // path.push_back(pos);
        if(lastPose.second >= h && pos.second <= h) xError = ((h-lastPose.first)*lastPose.second + (h - pos.second) * pos.first) / (lastPose.second - pos.second) - d;
        if(pos.second < -1) return SimRes{false, xError, maxHeight}; // tell when stopped or missed
        if(hit(pos, d)) {
            // paths.push_back(path);
            return SimRes{true, xError, maxHeight}; // can possibly add another condition to make the trajectory go above a certain point
        }
    }
    return SimRes{false, xError, maxHeight};
}

int main() {
    for(double distance = 0.3; distance <= 15; distance += 0.15) {
        for(double radialVel = -5.0; radialVel <= 5.0; radialVel += 0.3) {
    double minRobustness = 1000000;
    SimRes best = SimRes{false, -10, -1};
    double bestVel;
    double bestAngle;
    for(double velMag = 4; velMag < 16; velMag += 0.2){
        for(double velAngle = 0; velAngle < 90; velAngle += 1){
            auto cur = simulate(velMag, velAngle, radialVel, distance);
            if(cur.hit) {
                // calculate derrivative here then if path is more optimal say it
                double velocityRobustness = 
                    (simulate(velMag + velocityInaccuracy, velAngle, radialVel, distance).xError - simulate(velMag - velocityInaccuracy, velAngle, radialVel, distance).xError) / (2*velocityInaccuracy);
                double angleRobustness =
                    (simulate(velMag, velAngle + angleInaccuracy, radialVel, distance).xError - simulate(velMag, velAngle - angleInaccuracy, radialVel, distance).xError) / (2*angleInaccuracy);
                double robustness = angleRobustnessCoefficient*pow(angleRobustness, 2) + velocityRobustnessCoefficient*pow(velocityRobustness, 2) + 0.25 * cur.maxHeight + abs(0.5*cur.xError);
                if(robustness < minRobustness) {
                    minRobustness = robustness;
                    best = cur;
                    bestVel = velMag;
                    bestAngle = velAngle;
                }
            }
        }
    }
    if(best.hit) solutions.push_back({distance, radialVel, bestVel, bestAngle, minRobustness});
    }
    }
    saveToCSV(solutions, "shootingSolutions.csv");
}