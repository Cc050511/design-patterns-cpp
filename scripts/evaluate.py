#!/usr/bin/env python3
"""Design Pattern Evaluation Engine v3 - Test-based evaluation"""

import json
import os
import re
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Tuple

class PatternEvaluator:
    def __init__(self, criteria_file: str, build_dir: str, src_dir: str):
        with open(criteria_file, 'r') as f:
            self.criteria = json.load(f)['patterns']
        self.build_dir = Path(build_dir)
        self.src_dir = Path(src_dir)
        self.results = {}
        self.total_score = 0
        self.max_score = 0
        self.passing_score = 75

    def evaluate_all(self) -> Dict:
        print("=" * 70)
        print("Design Pattern Evaluation Engine v3")
        print("Templates removed main() - tests validate class implementations")
        print("=" * 70)
        print()

        for pattern_name in sorted(self.criteria.keys()):
            criteria = self.criteria[pattern_name]
            self.max_score += 100
            score = self.evaluate_pattern(pattern_name, criteria)
            self.total_score += score
            self.results[pattern_name] = {
                'score': score,
                'criteria': criteria,
                'passed': score >= self.passing_score
            }

        self.print_summary()
        return self.results

    def evaluate_pattern(self, pattern_name: str, criteria: Dict) -> int:
        print(f"\n--- Evaluating: {criteria['name']} ---")
        score = 0
        details = []

        compile_result = self.check_compilation(pattern_name)
        if compile_result:
            score += criteria['scores']['compilation']
            details.append(f"[PASS] Compilation (+{criteria['scores']['compilation']})")
        else:
            details.append(f"[FAIL] Compilation (0)")

        structure_score, structure_details = self.check_structure(pattern_name, criteria)
        score += structure_score
        details.extend(structure_details)

        runtime_result = False
        output = ""
        if compile_result:
            runtime_result, output = self.run_executable(pattern_name)
            if runtime_result:
                details.append(f"[PASS] Runtime execution")
            else:
                details.append(f"[FAIL] Runtime execution (crashed)")
        else:
            details.append(f"[SKIP] Runtime execution (compilation failed)")

        if compile_result and runtime_result:
            behavior_score, behavior_details = self.check_behavior(pattern_name, criteria, output)
            score += behavior_score
            details.extend(behavior_details)
        else:
            details.append(f"[SKIP] Behavior checks (runtime failed)")

        if compile_result and runtime_result:
            quality_score, quality_details = self.check_output_quality(pattern_name, criteria, output)
            score += quality_score
            details.extend(quality_details)
        else:
            details.append(f"[SKIP] Output quality (runtime failed)")

        if compile_result and runtime_result:
            ref_score, ref_details = self.check_against_reference(pattern_name, output)
            score += ref_score
            details.extend(ref_details)
        else:
            details.append(f"[SKIP] Reference comparison (runtime failed)")

        for detail in details:
            print(f"  {detail}")
        
        print(f"  Score: {score}/100")
        return score

    def check_compilation(self, pattern_name: str) -> bool:
        binary = self.build_dir / pattern_name
        return binary.exists()

    def run_executable(self, pattern_name: str) -> Tuple[bool, str]:
        binary = self.build_dir / pattern_name
        try:
            result = subprocess.run(
                [str(binary)],
                capture_output=True,
                text=True,
                timeout=5
            )
            return result.returncode == 0, result.stdout + result.stderr
        except Exception as e:
            return False, ""

    def check_structure(self, pattern_name: str, criteria: Dict) -> Tuple[int, List[str]]:
        score = 0
        details = []
        
        main_files = list(self.src_dir.rglob(f"*/{pattern_name}*/main.cpp"))
        if not main_files:
            details.append(f"[FAIL] Structure: main.cpp not found")
            return 0, details

        main_file = main_files[0]
        with open(main_file, 'r') as f:
            lines = f.readlines()
        
        code_lines = []
        in_multiline_comment = False
        for line in lines:
            stripped = line.strip()
            if in_multiline_comment:
                if '*/' in stripped:
                    in_multiline_comment = False
                continue
            if stripped.startswith('//'):
                continue
            if stripped.startswith('/*'):
                if '*/' not in stripped:
                    in_multiline_comment = True
                continue
            code_lines.append(line)
        
        code_content = ''.join(code_lines)

        structure_checks = criteria['structure_checks']
        score_per_item = structure_checks.get('score_per_item', 6.25)
        
        for check in structure_checks['must_have']:
            pattern = check['pattern']
            description = check['description']
            if re.search(pattern, code_content, re.IGNORECASE):
                score += score_per_item
                details.append(f"[PASS] Structure: {description} (+{score_per_item:.1f})")
            else:
                details.append(f"[FAIL] Structure: {description} (missing)")

        return score, details

    def check_behavior(self, pattern_name: str, criteria: Dict, output: str) -> Tuple[int, List[str]]:
        score = 0
        details = []
        
        behavior_checks = criteria['behavior_checks']
        score_per_item = behavior_checks.get('score_per_item', 15)
        
        for check in behavior_checks['must_have']:
            keywords = check['keyword'].split('|')
            description = check['description']
            found = any(kw.lower() in output.lower() for kw in keywords)
            
            if found:
                score += score_per_item
                details.append(f"[PASS] Behavior: {description} (+{score_per_item:.1f})")
            else:
                details.append(f"[FAIL] Behavior: {description} (missing in test output)")

        return score, details

    def check_output_quality(self, pattern_name: str, criteria: Dict, output: str) -> Tuple[int, List[str]]:
        score = 0
        details = []
        quality = criteria['output_quality']
        
        non_empty_lines = len([line for line in output.split('\n') if line.strip()])
        if non_empty_lines >= quality['min_lines']:
            score += 5
            details.append(f"[PASS] Output: {non_empty_lines} lines (>= {quality['min_lines']})")
        else:
            details.append(f"[FAIL] Output: {non_empty_lines} lines (< {quality['min_lines']})")

        required_found = True
        for keyword in quality['required_keywords']:
            if keyword.lower() not in output.lower():
                required_found = False
                details.append(f"[FAIL] Output: missing '{keyword}'")
        
        if required_found:
            score += 3
            details.append(f"[PASS] Output: all required keywords present")

        forbidden_found = False
        for keyword in quality['forbidden_keywords']:
            if keyword.lower() in output.lower():
                forbidden_found = True
                details.append(f"[FAIL] Output: forbidden keyword '{keyword}' found")
        
        if not forbidden_found:
            score += 2
            details.append(f"[PASS] Output: no forbidden keywords")

        return score, details

    def check_against_reference(self, pattern_name: str, user_output: str) -> Tuple[int, List[str]]:
        score = 0
        details = []
        
        reference_file = Path(f".reference/{pattern_name}.cpp")
        if not reference_file.exists():
            details.append(f"[SKIP] Reference: no reference implementation")
            return 0, details

        ref_binary = f".reference/{pattern_name}_ref"
        try:
            compile_result = subprocess.run(
                ["g++", "-std=c++23", str(reference_file), "-o", ref_binary],
                capture_output=True,
                timeout=30
            )
            
            if compile_result.returncode != 0:
                details.append(f"[SKIP] Reference: compilation failed")
                return 0, details
            
            result = subprocess.run(
                [f"./{ref_binary}"],
                capture_output=True,
                text=True,
                timeout=5
            )
            ref_output = result.stdout + result.stderr
            
            user_lines = set(line.strip().lower() for line in user_output.split('\n') if line.strip())
            ref_lines = set(line.strip().lower() for line in ref_output.split('\n') if line.strip())
            common = user_lines & ref_lines
            
            similarity = len(common) / max(len(ref_lines), 1) if ref_lines else 0
            
            if similarity >= 0.5:
                score = 10
                details.append(f"[PASS] Reference: {similarity:.1%} similarity (+10)")
            elif similarity >= 0.3:
                score = 5
                details.append(f"[WARN] Reference: {similarity:.1%} similarity (+5)")
            else:
                details.append(f"[FAIL] Reference: {similarity:.1%} similarity (0)")
        
        except Exception as e:
            details.append(f"[SKIP] Reference: error - {e}")
        finally:
            if os.path.exists(ref_binary):
                os.remove(ref_binary)

        return score, details

    def print_summary(self):
        print("\n" + "=" * 70)
        print("EVALUATION SUMMARY")
        print("=" * 70)

        passed = sum(1 for r in self.results.values() if r['passed'])
        total = len(self.results)

        print(f"\nTotal Score: {self.total_score}/{self.max_score}")
        print(f"Patterns Passed (>=75): {passed}/{total}")
        print()

        for pattern_name, result in sorted(self.results.items()):
            status = "PASS" if result['passed'] else "FAIL"
            print(f"  {status:4} {pattern_name:35} {result['score']:3}/100")

        print()
        if passed == total:
            print("All patterns passed evaluation!")
        else:
            print(f"{total - passed} pattern(s) need improvement.")

        print("=" * 70)

    def generate_report(self, output_file: str):
        report = []
        report.append("# Design Pattern Evaluation Report")
        report.append("")
        report.append(f"**Total Score**: {self.total_score}/{self.max_score}")
        report.append("")
        
        passed = sum(1 for r in self.results.values() if r['passed'])
        total = len(self.results)
        report.append(f"**Passed**: {passed}/{total}")
        report.append("")
        
        report.append("## Results")
        report.append("")
        report.append("| Pattern | Score | Status |")
        report.append("|---------|-------|--------|")
        
        for pattern_name, result in sorted(self.results.items()):
            status = "PASS" if result['passed'] else "FAIL"
            report.append(f"| {pattern_name} | {result['score']}/100 | {status} |")
        
        with open(output_file, 'w') as f:
            f.write('\n'.join(report))
        
        print(f"\nReport saved to: {output_file}")


def main():
    if len(sys.argv) < 2:
        build_dir = "build"
        src_dir = "src"
    else:
        build_dir = sys.argv[1]
        src_dir = sys.argv[2] if len(sys.argv) > 2 else "src"

    criteria_file = "scripts/evaluation_criteria.json"

    if not os.path.exists(criteria_file):
        print(f"Error: Criteria file not found: {criteria_file}")
        sys.exit(1)

    evaluator = PatternEvaluator(criteria_file, build_dir, src_dir)
    results = evaluator.evaluate_all()
    evaluator.generate_report("evaluation_report.md")
    
    all_passed = all(r['passed'] for r in results.values())
    sys.exit(0 if all_passed else 1)


if __name__ == "__main__":
    main()
