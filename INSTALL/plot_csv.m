clear all;
close all;

file = csvread('~/Desktop/SERIAL_20180906T03522540263Z.csv');
plot = 0;
T = 500; % samples
N0 = 1; % initial frame
n = floor(length(file)/T); % frames
h = 2; % header skip
N = N0 + n - 1;
wait = 2; % seconds

if plot
  for i = N0:N
    t0 = (i - 1) * T + N0 + 1;
    tn =  t0 + T;
    t = t0:tn;
    scatter(t,file(t,2), '.');
    line(t,file(t,2));
    title(['Frame ', num2str(i), ' / ', num2str(n)]);
    ylim([-10,10]);
    pause(wait);
  end
else
  diff = file(:,2).*(abs(file(:,2)) > 5.1);
  scatter(file((h+1):length(file),1), diff((h+1):length(file))); 
end