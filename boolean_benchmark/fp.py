#!/usr/bin/env python3

import os, sys, argparse, time, math
import maboss
import pandas




def main(*argv):

    parser = argparse.ArgumentParser(description='Parse script')
    parser.add_argument('method', type=str, help='the method used to search for fixed points')
    parser.add_argument('model', type=str, help='the model used in which to search the fixed points')
    parser.add_argument('--condition', type=str, default="wt", help='the condition to simulate')
    parser.add_argument('--iterations', type=int, default=100, help='the number of iterations used in the method')
    parser.add_argument('--maxtime', type=int, default=1000, help='the duration of the simulation in the method')
    parser.add_argument('--nbcores', type=int, default=10, help='the number of cores used in the simulation of the method')
    parser.add_argument('--replicates', type=int, default=3, help='the number of replicates of simulations')
    args = parser.parse_args()
    if args.method == "maboss":
        maboss_fixedpoints(args.model, args.condition, args.iterations, args.maxtime, args.nbcores)

def compute_precision_recall(model, condition, fps):

    # Collect the list of fixed points
    fps = [" -- ".join(sorted(state.split(" -- "))) for state in fps]

    # Loading source of truth
    all_fps = list(pandas.read_csv("results/%s_%s/res_fp.csv" % (model, condition), sep="\t", skiprows=1)["State"].values)
    all_fps = [" -- ".join(sorted(state.split(" -- "))) for state in all_fps]

    # The minimum amount of false negative is the total count minus our count
    false_negative = len(all_fps) - len(fps)
    true_positive = 0
    false_positive = 0
    for state in fps:
        if state in all_fps:
            # We found a real fixpoint : increase true positive
            true_positive += 1
        else:
            # We found a false fixpoint : increase false positive, but also false negative (as we missed one more)
            false_positive += 1
            false_negative += 1
    
    precision = true_positive / (true_positive + false_positive)
    recall = true_positive / (true_positive + false_negative)

    return precision, recall

def maboss_fixedpoints(model, condition, iterations, maxtime, nbcores, replicates=3):
    m = None

    try:
        m = maboss.loadSBML("models/%s.sbml" % model, "models/%s_%s.cfg" % (model, condition))
    except FileNotFoundError:
        print("Unknown model %s" % model, file=sys.stderr)
        return

    # Setting random initial state
    for node in m.network.keys():
        m.network.set_istate(node, [0.5, 0.5])

    # Setting simulation settings    
    m.update_parameters(use_physrandgen=True,sample_count=iterations, max_time=maxtime, time_tick=int(maxtime/4), thread_count=nbcores)
    
    precisions = []
    recalls = []
    durations = []

    for replicates in range(replicates):

        t0 = time.time()

        # Running the simulation
        res = m.run(cmaboss=True)

        t1 = time.time()

        fps = list(res.get_fptable()["State"].values)
        precision, recall = compute_precision_recall(model, condition, fps)

        precisions.append(precision)
        recalls.append(recall)
        durations.append(t1-t0)

    avg_precision = sum(precisions)/len(precisions)
    avg_recall = sum(recalls)/len(recalls)
    avg_duration = sum(durations)/len(durations)

    # print("%d fp found, %d fp missing, %d good one, %d false one, %.2gs" % (len(table_fps), missing, true_positive, false_positive, (t1-t0)))
    print("iterations = %d, precision = %.2g, recall = %.2g, %.2fs" % (iterations, avg_precision, avg_recall, avg_duration))
    # print(false_fps)
if __name__ == "__main__":
    main()
