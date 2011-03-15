# Copyright (c) 2007, 2009, 2011 Joseph Gaeddert
# Copyright (c) 2007, 2009, 2011 Virginia Polytechnic
# 				 Institute & State University
#
# This file is part of liquid.
#
# liquid is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# liquid is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with liquid.  If not, see <http://www.gnu.org/licenses/>.

# 
# Makefile for experimental module
#

module_name     := experimental

# local_s_files
#
# This is a list of local source files to compile into objects,
# referenced from the src/ subdirectory under $(local_dir)
#
local_s_files	:= 			\
	ann.nodes.c			\
	activation_functions.c		\
	cpmodem.c			\
	kmeans.c			\
	layer.c				\
	maxnet.c			\
	node.c				\
	fbasc.c				\
	gport.c				\
	filter_rrrf.c			\
	filter_crcf.c			\
	filter_cccf.c			\
	gmskframegen.c			\
	gmskframesync.c			\
	patternset.c			\
	awgn_channel.c			\
	lognorm_channel.c		\
	channel.c			\
	pamodel.c			\
	ricek_channel.c

# local_t_files
#
# This is a list of local autotest scripts (header files) which
# are used to generate the autotest program with the 'check'
# target.  These files are located under the tests/ subdirectory
# within $(local_dir)
#
local_t_files	:=			\
	ann_autotest.h			\
	gport_autotest.h		\
	channel_autotest.h


# local_b_files
#
# This is a list of local benchmark scripts which are used to
# generate the benchmark program with the 'bench' target.
# These files are located under the bench/ subdirectory within
# $(local_dir)
#
local_b_files	:=			\
	fbasc_benchmark.h		\
	gport_dma_benchmark.h		\
	gport_dma_threaded_benchmark.h	\
	gport_ima_benchmark.h		\
	gport_ima_threaded_benchmark.h	\
	dds_benchmark.h			\
	qmfb_benchmark.h

include common.mk

