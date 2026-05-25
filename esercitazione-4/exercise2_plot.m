% exercise2_plot.m
% Reads fourier_complex.csv and appends the plot to exercise2_plot.pdf.
% Also saves an SVG with the K value in the filename.
%
% Expected CSV format (no header row):
%   real part, imaginary part
%
% Usage: run this script from the folder containing the CSV file
%        after running the C program with the desired K value
%        >> exercise2_plot

clear; clc; close all;

%% Configuration
Fs      = 10000.0; % Sampling frequency [Hz]
f0      = 50.0;    % Fundamental frequency [Hz]
N       = 200;     % Number of samples
out_pdf = 'exercise2_plot.pdf';

%% Ask for K value (to name the SVG)
K = input('Inserire il valore di K usato per generare i campioni: ');

%% Load data
filename = 'fourier_complex.csv';
if ~isfile(filename)
    error('File "%s" not found. Make sure the C program has been run first.', filename);
end

data = readmatrix(filename);
re   = data(:, 1);
im   = data(:, 2);

%% Ideal trajectory on the complex plane
% x(t) takes values 1, j, -1, -j in each quarter period
re_ideal = [1,  0, -1,  0, 1];
im_ideal = [0,  1,  0, -1, 0];

%% Plot trajectory on the complex plane
fig = figure('Name', sprintf('Complex Fourier K=%d', K), 'NumberTitle', 'off');

plot(re_ideal(1:end-1), im_ideal(1:end-1), 'r.', 'MarkerSize', 15, ...
     'DisplayName', 'Traiettoria vera');
hold on;
plot([re; re(1)], [im; im(1)], 'Color', [0.2 0.4 0.8], 'LineWidth', 1.0, ...
     'DisplayName', sprintf('Approssimazione K=%d', K));

xlabel('Re\{x_n\}', 'Interpreter', 'tex');
ylabel('Im\{x_n\}', 'Interpreter', 'tex');
title(sprintf('Traiettoria nel piano complesso con K=%d', K));
legend('Location', 'best');
grid on;
axis equal;
box on;

% Remove toolbar
ax = gca;
ax.Toolbar.Visible = 'off';

%% Export
out_svg = sprintf('exercise2_K%d_plot.svg', K);
exportgraphics(fig, out_pdf, 'Resolution', 300, 'Append', true);
exportgraphics(fig, out_svg, 'Resolution', 300);
fprintf('Plot K=%d salvato in "%s" e "%s".\n', K, out_pdf, out_svg);