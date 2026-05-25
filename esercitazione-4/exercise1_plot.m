% exercise1_plot.m
% Reads fourier.csv and appends the plot to exercise1_plot.pdf.
% Also saves an SVG with the L value in the filename.
%
% Expected CSV format (no header row):
%   real part, imaginary part
%
% Usage: run this script from the folder containing the CSV file
%        after running the C program with the desired L value
%        >> exercise1_plot.m

clear; clc; close all;

%% Configuration
Fs      = 10000.0; % Sampling frequency [Hz]
f0      = 50.0;    % Fundamental frequency [Hz]
A       = 1.0;     % Amplitude [V]
N       = 1000;    % Number of samples
out_pdf = 'exercise1_plot.pdf';

%% Ask for L value (to name the SVG)
L = input('Inserire il valore di L usato per generare i campioni: ');

%% Load data
filename = 'fourier.csv';
if ~isfile(filename)
    error('File "%s" not found. Make sure the C program has been run first.', filename);
end

data = readmatrix(filename);
re   = data(:, 1);
t    = (0:length(re)-1) / Fs;

%% Ideal sawtooth signal
t_ideal = (0:N-1) / Fs;
x_ideal = A * mod(t_ideal, 1/f0) * f0;

%% Plot real part vs time
fig = figure('Name', sprintf('Fourier L=%d', L), 'NumberTitle', 'off');

plot(t_ideal, x_ideal, 'r-', 'LineWidth', 1.2, 'DisplayName', 'Segnale ideale');
hold on;
plot(t, re, 'Color', [0.2 0.4 0.8], 'LineWidth', 1.2, ...
     'DisplayName', sprintf('Approssimazione L=%d', L));

xlabel('Tempo [s]');
ylabel('Re\{x_n\}', 'Interpreter', 'tex');
title(sprintf('Approssimazione serie di Fourier con L=%d', L));
legend('Location', 'northwest');
grid on;
xlim([t(1) t(end)]);

% Remove toolbar
ax = gca;
ax.Toolbar.Visible = 'off';

%% Export
out_svg = sprintf('exercise1_L%d_plot.svg', L);
exportgraphics(fig, out_pdf, 'Resolution', 300, 'Append', true);
exportgraphics(fig, out_svg, 'Resolution', 300);
fprintf('Plot L=%d salvato in "%s" e "%s".\n', L, out_pdf, out_svg);