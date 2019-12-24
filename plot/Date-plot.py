# -*- coding: utf-8 -*-
"""
Created on Wed Feb 21 17:41:50 2018

@author: 梁杰
"""

import pandas as pd
import matplotlib as mpl
mpl.use('Agg')

import matplotlib.pyplot as plt
import sys
import matplotlib.ticker as tk
import matplotlib.dates as dates

def deal_plot_data_to_path(filename,aflname):
    plot_data = pd.read_csv(filename)
    #print(plot_data.columns)
    plot_data['# unix_time']=(plot_data['# unix_time']-plot_data.iat[0,0])/3600.0
    plot_data.rename(columns={'# unix_time' :'time(hours)'}, inplace = True)
    plot_data.rename(columns={' paths_total':aflname}, inplace = True)
    plot_data = plot_data[plot_data['time(hours)']<=24]
    plot_data = plot_data.drop_duplicates('time(hours)')
    plot_data = plot_data.set_index('time(hours)')
    #print(plot_data)
    return plot_data

# def deal_plot_data_to_crashes(filename,aflname):
#     plot_data = pd.read_csv(filename)
#     #print(plot_data.columns)
#     plot_data['# unix_time']=plot_data['# unix_time']-plot_data.iat[0,0]
#     plot_data.rename(columns={'# unix_time' :'time(s)'}, inplace = True)
#     plot_data.rename(columns={' unique_crashes':aflname}, inplace = True)
#     plot_data = plot_data.drop_duplicates('time(s)').set_index('time(s)')
#     #print(plot_data)
#     return plot_data

# def deal_plot_data_to_branches(filename,aflname):
#     plot_data = pd.read_csv(filename)
#     print(plot_data.columns)
#     plot_data['# unix_time']=plot_data['# unix_time']-plot_data.iat[0,0]
#     plot_data.rename(columns={'# unix_time' :'time(s)'}, inplace = True)
#     plot_data.rename(columns={' branches_total':aflname}, inplace = True)
#     #plot_data.rename(columns={' map_size':aflname}, inplace = True)
#     plot_data = plot_data.drop_duplicates('time(s)').set_index('time(s)')
#     #print(plot_data)
#     return plot_data


# polar_pro_name = "~/feilong/libiec104_fuzz/iec104-fuzz-new-3-13/IEC10X/OUT/plot_data"
# aflname = "./../pro//OUT-new/plot_data"
# aflfastname = "plot_data_aflfast"
# polar_name = "plot_data_polar1"
#filename2 = "plot_data_aflfast"
# aflname2 = "masterRAFL_plot_data"

polar_pro_name = sys.argv[1]
aflname = sys.argv[2]


name1 = 'FIAFL'
name2 = 'AFL'
# name3 = 'aflfast'
# name4 = 'polar'

plot_polar_pro_path=deal_plot_data_to_path(polar_pro_name,name1)
plot_afl_path=deal_plot_data_to_path(aflname,name2)
# plot_aflfast_path=deal_plot_data_to_path(aflfastname,name3)
# plot_polar_path=deal_plot_data_to_path(polar_name,name4)


# plot_polar_pro_branch=deal_plot_data_to_branches(polar_pro_name,name1)
# plot_afl_branch=deal_plot_data_to_branches(aflname,name2)
# plot_aflfast_branch=deal_plot_data_to_branches(aflfastname,name3)
# plot_polar_branch=deal_plot_data_to_branches(polar_name,name4)


pdata_polar_pro_path = pd.DataFrame(plot_polar_pro_path[name1])
pdata_afl_path = pd.DataFrame(plot_afl_path[name2])
# pdata_aflfast_path = pd.DataFrame(plot_aflfast_path[name3])
# pdata_polar_path = pd.DataFrame(plot_polar_path[name4])


# pdata_polar_pro_branch= pd.DataFrame(plot_polar_pro_branch[name1])
# pdata_afl_branch = pd.DataFrame(plot_afl_branch[name2])
# pdata_aflfast_branch = pd.DataFrame(plot_aflfast_branch[name3])
# pdata_polar_branch= pd.DataFrame(plot_polar_branch[name4])


df = pd.concat([pdata_polar_pro_path,pdata_afl_path], axis=1)
# df = pd.concat([pdata_polar_pro_path, pdata_afl_path, pdata_aflfast_path, pdata_polar_path], axis=1)
df=df.fillna(method='pad')
df.plot(figsize=(6,4),logx=False)
#pdata_polar_pro_path.plot()
#pdata_afl_path.plot()
plt.xlabel("Time(hours)")
plt.ylabel("Paths covered")
plt.legend(loc=4)
plt.text(1,1,"Higher is better")
plt.xlim(-1,25)
#fig,ax=plt.subplots()
ax = plt.subplot(111)
#ax.xaxis.set_major_locator(dates.HourLocator(byhour=range(24), interval=4)) 
ax.xaxis.set_major_locator(tk.FixedLocator([0,4,8,12,16,20,24]))
aax = plt.subplot
ax.plot(linestyle='--')
# dfb = pd.concat([pdata_polar_pro_branch], axis=1)
# # dfb = pd.concat([pdata_polar_pro_branch, pdata_afl_branch, pdata_aflfast_branch, pdata_polar_branch], axis=1)
# dfb=dfb.fillna(method='pad')
# dfb.plot(figsize=(6,4),logx=False)

# plt.show()
plt.savefig("result.png")
