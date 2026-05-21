% exercise2_plot.m
% Reads phasor.csv and plots:
%   1. The phasor samples on the complex plane
%   2. The real part of the samples as a function of time
%
% Expected CSV format (no header row):
%   real part, imaginary part
%
% Usage: run this script from the folder containing the CSV file
%        >> plot_phasor

clear; clc; close all;

%% Configuration
filename = 'phasor.csv';
Fs       = 1000.0;  % Sampling frequency [Hz]
out_pdf  = 'exercise1_plot.pdf';
out1_svg = 'exercise1_1_plot.svg';
out2_svg = 'exercise1_2_plot.svg'; 

if isfile(out_pdf), delete(out_pdf); end
if isfile(out1_svg), delete(out1_svg); end
if isfile(out2_svg), delete(out2_svg); end
%% Load data
if ~isfile(filename)
    error('File "%s" not found. Make sure the C program has been run first.', filename);
end

data = readmatrix(filename);
re   = data(:, 1);
im   = data(:, 2);
N    = length(re);
t    = (0:N-1) / Fs;  % Time axis [s]

%% Plot 1 - Phasor on the complex plane
fig1 = figure('Name', 'Phasor - Complex Plane', 'NumberTitle', 'off');

plot(re, im, 'MarkerSize', 2, 'Color', [0.2 0.4 0.8]);
xlabel('Re\{x_n\}', 'Interpreter', 'tex');
ylabel('Im\{x_n\}', 'Interpreter', 'tex');
title('Fasore sul piano complesso');
grid on;
axis equal;

% Remove toolbars
ax = gca;
ax.Toolbar.Visible = 'off';
exportgraphics(fig1, out_pdf, 'Resolution', 300);
exportgraphics(fig1, out1_svg, 'Resolution', 300);

%% Plot 2 - Real part vs time
fig2 = figure('Name', 'Phasor - Real Part', 'NumberTitle', 'off');

plot(t, re, 'Color', [0.2 0.4 0.8], 'LineWidth', 1.2);
xlabel('Tempo [s]');
ylabel('Re\{x_n\}', 'Interpreter', 'tex');
title('Parte reale del fasore in funzione del tempo');
grid on;
xlim([t(1) t(end)]);

% Remove toolbars
ax = gca;
ax.Toolbar.Visible = 'off';
exportgraphics(fig2, out_pdf, 'Resolution', 300, 'Append', true);
exportgraphics(fig2, out2_svg, 'Resolution', 300);
