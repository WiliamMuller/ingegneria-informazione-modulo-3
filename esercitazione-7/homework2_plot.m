% Reads DFT_SP.csv and plots the modulus of the DFT vector X vs frequency.
% This plot shows the spectral leakage phenomenon.
%
% Expected CSV format (no header row):
%   k, frequency (k*Δf), real part, imaginary part, modulus
%


clear; clc; close all;

%% Configuration
filename = 'FFT_SP.csv';
out_pdf  = 'homework2_plot.pdf';
out_svg  = 'homework2_plot.svg';

if isfile(out_pdf), delete(out_pdf); end
if isfile(out_svg), delete(out_svg); end

%% Load data
if ~isfile(filename)
    error('File "%s" not found. Make sure the C program has been run first.', filename);
end

data = readmatrix(filename);
freq = data(:, 2);
mag  = data(:, 5);

%% Plot modulus vs frequency
fig = figure('Name', 'FFT - Spectral Leakage', 'NumberTitle', 'off');

stem(freq, mag, 'filled', 'MarkerSize', 3, 'LineWidth', 1.0, ...
     'Color', [0.2 0.4 0.8]);

xlabel('Frequenza [Hz]');
ylabel('|X[k]|', 'Interpreter', 'tex');
title('Modulo della FFT - Spectral Leakage (f_0 = 2015 Hz)', ...
      'Interpreter', 'tex');
grid on;
xlim([min(freq) max(freq)]);

% Remove toolbar
ax = gca;
ax.Toolbar.Visible = 'off';

%% Export
exportgraphics(fig, out_pdf, 'Resolution', 300);
exportgraphics(fig, out_svg, 'Resolution', 300);
fprintf('Plot salvato in "%s" e "%s".\n', out_pdf, out_svg);