import unittest

import numpy as np
import pandas as pd

from compare_table1 import compare_table


class CompareTableTest(unittest.TestCase):
    def compare(self, name, column, baseline, new):
        key = "tool"
        a = pd.DataFrame([{key: "example", column: baseline}])
        b = pd.DataFrame([{key: "example", column: new}])
        return compare_table(name, a, b, 1e-6)[0]

    def test_impulse_percentage_roundoff_is_ignored(self):
        for column in ("plateau_rel_error_pct", "displacement_rel_error_pct"):
            with self.subTest(column=column):
                self.assertEqual(self.compare("mechanics_external_impulse.csv", column, 6e-11, 2e-11), [])
                self.assertEqual(self.compare("mechanics_external_impulse.csv", column, -4e-11, 4e-11), [])

    def test_impulse_percentage_real_changes_are_reported(self):
        for column in ("plateau_rel_error_pct", "displacement_rel_error_pct"):
            with self.subTest(column=column):
                self.assertEqual(len(self.compare("mechanics_external_impulse.csv", column, 0.0, 2e-10)), 1)
                self.assertEqual(len(self.compare("mechanics_external_impulse.csv", column, 2.0, 2.01)), 1)
                self.assertEqual(len(self.compare("mechanics_external_impulse.csv", column, np.nan, 0.0)), 1)

    def test_other_values_keep_original_absolute_tolerance(self):
        for name, column in (
            ("mechanics_external_impulse.csv", "displacement_um"),
            ("cell_cycle.csv", "displacement_rel_error_pct"),
        ):
            with self.subTest(name=name):
                self.assertEqual(len(self.compare(name, column, 0.0, 2e-11)), 1)


if __name__ == "__main__":
    unittest.main()
