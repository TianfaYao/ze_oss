#!/usr/bin/env python3
"""
Zurich Eye
"""

# This example shows how to:
# 1) Load two trajectories
# 2) Find closest timestamps
# 3) Align the trajectories
# 4) Compute error statistics

import logging
import ze_py.test.utils as test_utils
import ze_trajectory_analysis.analyse as traj_analysis

# Init logging.
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)
logger.info('Trajectory alignment example.')

data_dir = test_utils.get_test_data_dir('ze_applanix_gt_data')

ta = traj_analysis.TrajectoryAnalysis('.')
ta.load_data(data_dir)
ta.align_trajectory('se3', 300, -1)
ta.plot_aligned_trajectory()
ta.plot_estimator_results(data_dir)
ta.compute_rms_errors()

