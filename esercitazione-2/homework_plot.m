% plot.m
% Reads histogram.csv and plots the Empirical PDF against the Theoretical PDF
% of the Polynomial distribution f_Y(y) = 3y^2, 0 <= x <= 1.
%
% Expected CSV format (no header row):
%   y_mid, empirical PDF value
%
% Usage: run this script from the folder containing the CSV file
%        >> plot_pdf

clear; clc; close all;

%% Configuration
filename = 'histogram_hw.csv';
out_pdf  = 'homework_plot.pdf';
out_svg  = 'homework_plot.svg';

if isfile(out_pdf), delete(out_pdf); end
if isfile(out_svg), delete(out_svg); end

%% Load data
if ~isfile(filename)
    error('File "%s" not found. Make sure the C program has been run first.', filename);
end

data = readmatrix(filename);
y_mid = data(:, 1);
f_emp = data(:, 2);

%% Theoretical PDF
y_th = linspace(0, 1, 1000);
f_th = 3 * y_th .^ 2;

%% Plot
fig = figure('Name', 'Empirical vs Theoretical PDF', 'NumberTitle', 'off');

% Empirical PDF as a bar/stem plot
bar(y_mid, f_emp, 1, 'FaceColor', 'none', 'EdgeColor', [0.5 0 0.5], ...
    'DisplayName', 'PDF Empirica');
hold on;

% Theoretical PDF
plot(y_th, f_th, 'r-', 'LineWidth', 2, 'DisplayName', 'PDF Teorica');

xlabel('y');
ylabel('f_Y(y)');
title('PDF Empirica vs PDF Teorica (Distribuzione Polinomiale)');
legend('Location', 'northwest');
grid on;
xlim([0 1]);

exportgraphics(fig, out_pdf, 'Resolution', 300);
exportgraphics(fig, out_svg, 'Resolution', 300);
fprintf('Plot salvato in "%s".\n', out_pdf);
