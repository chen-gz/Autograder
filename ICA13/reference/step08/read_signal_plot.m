clear
clc

fname = 'diff_eqn_soln_x.txt';
if exist(fname) ~= 2
    fprintf(1,'File Does Not Exist!!!\n');
    return
end

fid = fopen(fname,'r');

line_from_file = fgetl(fid);
if ~strcmp(line_from_file, 'Time-Domain Signal Samples')
    fprintf(1,'Title Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

line_from_file = fgetl(fid);
if ~strcmp(line_from_file(1:4), 'N = ')
    fprintf(1,'Second Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

nSamp = str2num(line_from_file(5:end));

line_from_file = fgetl(fid);
if ~strcmp(line_from_file(1:5), 'fs = ')
    fprintf(1,'Third Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

fs = str2num(line_from_file(6:end));

line_from_file = fgetl(fid);
if ~strcmp(line_from_file(1:5), 't0 = ')
    fprintf(1,'Fourth Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

t0 = str2num(line_from_file(6:end));

line_from_file = fgetl(fid);
if ~strcmp(line_from_file(1:13), 'Signal label:')
    fprintf(1,'Fifth Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

label = str2num(line_from_file(14:end));

line_from_file = fgetl(fid);
if ~strcmp(line_from_file, 'Mathematical expression')
    fprintf(1,'Sixth Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

line_from_file = fgetl(fid);
fprintf(1,[line_from_file '\n']);

line_from_file = fgetl(fid);
if ~strcmp(line_from_file, 'Time and signal samples in .csv format')
    fprintf(1,'Eighth Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

line_from_file = fgetl(fid);
if ~strcmp(line_from_file, 't, x(t)')
    fprintf(1,'Ninth Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

line_from_file = fgetl(fid);
if ~strcmp(line_from_file, '-------')
    fprintf(1,'Tenth Line Incorrect!!!\n');
    return
end
fprintf(1,[line_from_file '\n']);

t = zeros(1,nSamp);
s = zeros(1,nSamp);
n = 1;

while ~feof(fid)
    line_from_file = fgetl(fid);
    comma_index = find(line_from_file == ',',1);
    t(n) = str2num(line_from_file(1:comma_index-1));
    s(n) = str2num(line_from_file(comma_index+1:end));
    n = n+1;
end

figure(1)
plot(t,s,'b')
if min(s) == max(s)
    axis([min(t) max(t) min(s)-1 max(s)+1])
else
    axis([min(t) max(t) min(s) max(s)])
end
xlabel('time   (sec)')
ylabel('Signal values')
title('Plot of Time-Domain Signal')

    

    