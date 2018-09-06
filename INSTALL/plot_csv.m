clear all;
close all;
% Frame by frame CSV file plotter
%----------------------------%

file = csvread('~/Desktop/LETSFINDOUT_20180906T223821926498Z.csv');
plot = 1;
T = 500; % samples per frame
N0 = 64; % initial frame
wait = 1; % delay in seconds

%----------------------------%

h = 2; % header skip
if plot
  N = floor(length(file) / T); % max allowable frames
  if N0 < 1 || N0 > N
    break;
  end
  for i = N0:N
    t0 = T * (i - 1) + N0 + 1;
    t =  t0 + T;
    ti = t0:t;
    scatter(ti, file(ti, 2), '.');
    line(ti, file(ti, 2));
    title(['Frame ', num2str(i), ' / ', num2str(N)]);
    ylim([-10, 10]);
    xlim([-inf, t]);
    xlabel('sample');
    ylabel('V');
    pause(wait);
  end
else
  thres = 5.1; % 5V + 2%
  start = h + 1;
  stop = length(file);
  diff = file(start:stop, 2).*(abs(file(start:stop, 2)) > 5.1);
  indices = find(diff > 0);
  scatter(file(indices, 1), diff(indices)); 
  grid on;
  title('Dropoffs');
  xlabel('sample');
  ylabel('V');
end