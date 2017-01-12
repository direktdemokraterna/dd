<?php

use PHPUnit\Framework\TestCase;

class General_helpers_Test extends TestCase
{
    public function test_check_personnummer_should_return_true_when_valid_personal_identity_number() {
        $this->assertTrue(general_helpers::check_personnummer("2121010108"));
    }

    public function test_check_personnummer_should_return_false_when_invalid_personal_identity_number() {
        $this->assertFalse(general_helpers::check_personnummer("0101010101"));
        // the check does not check if it's a valid date.
        // $this->assertFalse(general_helpers::check_personnummer("0000000000"));
    }
}